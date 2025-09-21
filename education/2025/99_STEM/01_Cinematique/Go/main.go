package main

import "fmt"
import "Go/libraries"

func main() {
	v0 := physique.KmH_ms(72) // 72 km/h -> 20 m/s
	a := 2.0                  // accélération (m/s²)
	t := 5.0                  // temps (s)

	vitesseFinale := physique.VitesseFinale(v0, a, t)
	distance := physique.DistanceAvecAcceleration(v0, a, t)

	fmt.Printf("Vitesse finale: %.2f m/s\n", vitesseFinale)
	fmt.Printf("Distance parcourue: %.2f m\n", distance)
}
