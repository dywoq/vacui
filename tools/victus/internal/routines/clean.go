// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package routines

import (
	"fmt"
	"os/exec"
	"path"

	"github.com/dywoq/vacui/tools/victus/internal/gnumake"
	"github.com/dywoq/vacui/tools/victus/internal/logging"
	"github.com/dywoq/vacui/tools/victus/internal/module"
	"github.com/dywoq/vacui/tools/victus/internal/toolchain"
)

// ModuleClean works the same as [ModuleBuild], but it inserts a "clean"
// recipe instead of the "all" recipe. Returns an error if it failed
// to delete build artifacts.
func ModuleClean(dir string, t *toolchain.Toolchain, b gnumake.BuildType, customVars map[string]string) error {
	modulePath := path.Join(dir, "victus.toml")
	m, err := module.ParseFile(modulePath)
	if err != nil {
		return err
	}

	if m.General.Type == module.TypeRegular {
		logging.Infof("\t| REGULAR MODULE %q |\n", dir)
		return moduleCleanRegular(dir, m, t, b, customVars)
	}
	if m.General.Type == module.TypeWorkspace {
		logging.Infof("\t| WORKSPACE MODULE %q |\n", dir)
		return moduleCleanWorkspace(dir, m, t, b, customVars)
	}

	return fmt.Errorf("unknown module type: %s", m.General.Type)
}

func moduleCleanRegular(dir string, m *module.Config, t *toolchain.Toolchain, b gnumake.BuildType, customVars map[string]string) error {
	if len(m.Info.Regular.Dependencies) != 0 {
		logging.Infof("%q - Detected module dependencies, cleaning them first\n", dir)
	}
	for _, depend := range m.Info.Regular.Dependencies {
		dependPath := path.Join(dir, depend)
		err := ModuleClean(dependPath, t, b, customVars)
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
	cmd, err := gnumake.GenerateCmd([]string{"clean"}, m, finalToolchain, b, customVars)
	if err != nil {
		return err
	}
	logging.Infof("%q - Running GNU Make\n", dir)
	realCmd := exec.Command(cmd.Executable, cmd.Args...)
	realCmd.Dir = dir
	output, err := realCmd.CombinedOutput()
	if err != nil {
		return fmt.Errorf("cleaning the module %q failed:\n%q", dir, string(output))
	}
	logging.Infof("%q - Cleaning done!\n", dir)
	return nil
}

func moduleCleanWorkspace(dir string, m *module.Config, t *toolchain.Toolchain, b gnumake.BuildType, customVars map[string]string) error {
	if len(m.Info.Workspace.Modules) != 0 {
		logging.Infof("%q - Detected workspace modules\n", dir)
	}
	for _, mod := range m.Info.Workspace.Modules {
		logging.Infof("%q - Cleaning a workspace module %q\n", dir, mod)
		moduleDir := path.Join(dir, mod)
		err := ModuleClean(moduleDir, t, b, customVars)
		if err != nil {
			return fmt.Errorf("failed to clean the workspace module %q: %v\n", moduleDir, err)
		}
	}
	return nil
}
