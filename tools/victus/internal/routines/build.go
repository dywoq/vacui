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

// ModuleBuild opens a configuration file, which is named victus.toml, in the
// specified module directory. Depending on the module type, the function
// may activate the following procedures:
//
//   - If it is [module.TypeRegular], then the function builds a regular
//     module. The function builds dependencies first, recursively calling itself.
//
//   - If it is [module.TypeWorkspace], then the function builds modules,
//     specified in the workspace module. It recursively calls itself.
//
// The provided toolchain applies to all modules being built. It requires
// Makefile of modules to have a "all" building rule.
//
// Returns an error if one of the modules failed to build.
func ModuleBuild(dir string, t *toolchain.Toolchain, b gnumake.BuildType, customVars map[string]string) error {
	modulePath := path.Join(dir, "victus.toml")
	m, err := module.ParseFile(modulePath)
	if err != nil {
		return err
	}
	if m.General.Type == module.TypeRegular {
		logging.Infof("\t| REGULAR MODULE %q |\n", dir)
		return moduleBuildRegular(dir, m, t, b, customVars)
	}
	if m.General.Type == module.TypeWorkspace {
		logging.Infof("\t| WORKSPACE MODULE %q |\n", dir)
		return moduleBuildWorkspace(dir, m, t, b, customVars)
	}
	return fmt.Errorf("unknown module type: %s", m.General.Type)
}

func moduleBuildWorkspace(dir string, m *module.Config, t *toolchain.Toolchain, b gnumake.BuildType, customVars map[string]string) error {
	if len(m.Info.Workspace.Modules) != 0 {
		logging.Infof("%q - Detected workspace modules\n", dir)
	}
	for _, mod := range m.Info.Workspace.Modules {
		logging.Infof("%q - Building a workspace module %q\n", dir, mod)
		moduleDir := path.Join(dir, mod)
		err := ModuleBuild(moduleDir, t, b, customVars)
		if err != nil {
			return fmt.Errorf("failed to build the workspace module %q: %v\n", moduleDir, err)
		}
	}
	return nil
}

func moduleBuildRegular(dir string, m *module.Config, t *toolchain.Toolchain, b gnumake.BuildType, customVars map[string]string) error {
	if len(m.Info.Regular.Dependencies) != 0 {
		logging.Infof("%q - Detected module dependencies, building them first\n", dir)
	}
	for _, depend := range m.Info.Regular.Dependencies {
		dependPath := path.Join(dir, depend)
		err := ModuleBuild(dependPath, t, b, customVars)
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
	logging.Infof("%q - Running GNU Make\n", dir)
	realCmd := exec.Command(cmd.Executable, cmd.Args...)
	realCmd.Dir = dir
	output, err := realCmd.CombinedOutput()
	if err != nil {
		return fmt.Errorf("building the module %q failed:\n%q", dir, string(output))
	}
	logging.Infof("%q - Building done!\n", dir)
	return nil
}
