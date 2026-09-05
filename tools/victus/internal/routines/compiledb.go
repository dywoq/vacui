// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package routines

import (
	"fmt"
	"os/exec"
	"path"
	"slices"

	"github.com/dywoq/vacui/tools/victus/internal/gnumake"
	"github.com/dywoq/vacui/tools/victus/internal/logging"
	"github.com/dywoq/vacui/tools/victus/internal/module"
	"github.com/dywoq/vacui/tools/victus/internal/toolchain"
)

// ModuleGenerateCompileDatabase works the same as [ModuleBuild] function,
// but in addition, it generates a compilation database in modules. It relies
// on the bear command utility to generate the database. Returns an error
// if it failed to do so.
func ModuleGenerateCompileDatabase(dir string, t *toolchain.Toolchain, b gnumake.BuildType, customVars map[string]string) error {
	modulePath := path.Join(dir, "victus.toml")
	m, err := module.ParseFile(modulePath)
	if err != nil {
		return err
	}

	if m.General.Type == module.TypeRegular {
		logging.Infof("\t| REGULAR MODULE %q |\n", dir)
		return moduleGenerateCompileDatabaseRegular(dir, m, t, b, customVars)
	}
	if m.General.Type == module.TypeWorkspace {
		logging.Infof("\t| REGULAR MODULE %q |\n", dir)
		return moduleGenerateCompileDatabaseWorkspace(dir, m, t, b, customVars)
	}

	return fmt.Errorf("unknown module type: %s", m.General.Type)
}

func moduleGenerateCompileDatabaseRegular(dir string, m *module.Config, t *toolchain.Toolchain, b gnumake.BuildType, customVars map[string]string) error {
	for _, depend := range m.Info.Regular.Dependencies {
		dependPath := path.Join(dir, depend)
		err := ModuleGenerateCompileDatabase(dependPath, t, b, customVars)
		if err != nil {
			return err
		}
	}
	finalToolchain := t
	if len(m.Info.Regular.ForcedToolchain) != 0 {
		logging.Infof("%q - Detected a forced toolchain path, parsing it\n", dir)
		forcedToolchainPath := path.Join(dir, m.Info.Regular.ForcedToolchain)
		forcedToolchain, err := toolchain.ParseFile(forcedToolchainPath)
		if err != nil {
			return fmt.Errorf("failed to parse the forced toolchain file %q: %v", forcedToolchainPath, err)
		}
		finalToolchain = forcedToolchain
	}
	cmd, err := gnumake.GenerateCmd([]string{"all"}, m, finalToolchain, b, customVars)
	if err != nil {
		return err
	}
	logging.Infof("%q - Running Bear\n", dir)
	cmd.Executable = "bear"
	cmd.Args = slices.Concat([]string{"--", "make"}, cmd.Args)
	realCmd := exec.Command(cmd.Executable, cmd.Args...)
	realCmd.Dir = dir
	output, err := realCmd.CombinedOutput()
	if err != nil {
		return fmt.Errorf("generating compilation database in the module %q failed:\n%q", dir, string(output))
	}
	logging.Infof("%q - Generating compilation database done!\n", dir)
	return nil
}

func moduleGenerateCompileDatabaseWorkspace(dir string, m *module.Config, t *toolchain.Toolchain, b gnumake.BuildType, customVars map[string]string) error {
	if len(m.Info.Workspace.Modules) != 0 {
		logging.Infof("%q - Detected workspace modules\n", dir)
	}
	for _, mod := range m.Info.Workspace.Modules {
		logging.Infof("%q - Generating compilation database in a module %q\n", dir, mod)
		moduleDir := path.Join(dir, mod)
		err := ModuleGenerateCompileDatabase(moduleDir, t, b, customVars)
		if err != nil {
			return fmt.Errorf("failed to generate compilation database in the workspace module %q: %v\n", moduleDir, err)
		}
	}
	return nil
}
