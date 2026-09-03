// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package routines

import (
	"fmt"
	"os/exec"
	"path"

	"github.com/dywoq/vacui/tools/victus/internal/gnumake"
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
		return moduleCleanRegular(dir, m, t, b, customVars)
	}
	if m.General.Type == module.TypeWorkspace {
		return moduleCleanWorkspace(dir, m, t, b, customVars)
	}

	return fmt.Errorf("unknown module type: %s", m.General.Type)
}

func moduleCleanRegular(dir string, m *module.Config, t *toolchain.Toolchain, b gnumake.BuildType, customVars map[string]string) error {
	for _, depend := range m.Info.Regular.Dependencies {
		dependPath := path.Join(dir, depend)
		err := ModuleClean(dependPath, t, b, customVars)
		if err != nil {
			return err
		}
	}
	finalToolchain := t
	if len(m.Info.Regular.ForcedToolchain) != 0 {
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
	realCmd := exec.Command(cmd.Executable, cmd.Args...)
	realCmd.Dir = dir
	output, err := realCmd.CombinedOutput()
	if err != nil {
		return fmt.Errorf("cleaning the module %q failed:\n%q", dir, string(output))
	}
	return nil
}

func moduleCleanWorkspace(dir string, m *module.Config, t *toolchain.Toolchain, b gnumake.BuildType, customVars map[string]string) error {
	for _, mod := range m.Info.Workspace.Modules {
		moduleDir := path.Join(dir, mod)
		err := ModuleClean(moduleDir, t, b, customVars)
		if err != nil {
			return fmt.Errorf("failed to clean the workspace module %q: %v\n", moduleDir, err)
		}
	}
	return nil
}
