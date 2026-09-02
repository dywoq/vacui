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
func ModuleClean(dir string, t *toolchain.Toolchain) error {
	modulePath := path.Join(dir, "victus.toml")
	m, err := module.ParseFile(modulePath)
	if err != nil {
		return err
	}

	if m.General.Type == module.TypeRegular {
		return moduleCleanRegular(dir, m, t)
	}
	if m.General.Type == module.TypeWorkspace {
		return moduleCleanWorkspace(dir, m, t)
	}

	return fmt.Errorf("unknown module type: %s", m.General.Type)
}

func moduleCleanRegular(dir string, m *module.Config, t *toolchain.Toolchain) error {
	for _, depend := range m.Info.Regular.Dependencies {
		dependPath := path.Join(dir, depend)
		err := ModuleClean(dependPath, t)
		if err != nil {
			return err
		}
	}
	cmd, err := gnumake.GenerateCmd([]string{"clean"}, m, t)
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

func moduleCleanWorkspace(dir string, m *module.Config, t *toolchain.Toolchain) error {
	for _, mod := range m.Info.Workspace.Modules {
		moduleDir := path.Join(dir, mod)
		err := ModuleClean(moduleDir, t)
		if err != nil {
			return fmt.Errorf("failed to clean the workspace module %q: %v\n", moduleDir, err)
		}
	}
	return nil
}
