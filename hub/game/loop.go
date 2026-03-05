package game

import (
	"github.com/hajimehoshi/ebiten/v2"
)

type Loop struct {
}


func (l *Loop) Update() error {
	return nil
}

func (l *Loop) Draw(screen *ebiten.Image) {}

func (l *Loop) Layout(int, int) (int, int) {
	return 640, 480
}
