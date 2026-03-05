package hub

import (
	"voidmare/hub/game"

	"github.com/hajimehoshi/ebiten/v2"
)

func Start() error {
	l := &game.Loop{}
	ebiten.SetWindowSize(640, 480)
	ebiten.SetWindowTitle("VOIDMARE")
	ebiten.SetWindowResizingMode(ebiten.WindowResizingModeEnabled)
	err := ebiten.RunGame(l)
	if err != nil {
		return err
	}
	return nil
}

func Shutdown() {}
