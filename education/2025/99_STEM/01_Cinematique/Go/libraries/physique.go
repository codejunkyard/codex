package physique

import "math"

// Acceleration: calcule l'accélération donnée la variation de vitesse et le temps.
// vf = vitesse finale (m/s), vi = vitesse initiale (m/s), t = temps (s).
func Acceleration(vitesseFinale, vitesseInitiale, temps float64) float64 {
	if temps == 0 {
		return math.NaN() // éviter la division par zéro
	}
	return (vitesseFinale - vitesseInitiale) / temps
}

// KmH_ms: convertit km/h en m/s.
func KmH_ms(kmh float64) float64 {
	return kmh / 3.6
}

// ms_KmH: convertit m/s en km/h.
func ms_KmH(ms float64) float64 {
	return ms * 3.6
}

// DistanceVitesseConstante: calcule la distance parcourue à vitesse constante.
// v = vitesse (m/s), t = temps (s).
func DistanceVitesseConstante(vitesse, temps float64) float64 {
	return vitesse * temps
}

// DistanceAvecAcceleration: calcule la distance donnée la vitesse initiale, l'accélération et le temps.
// Utilise : s = vi * t + 0.5 * a * t²
func DistanceAvecAcceleration(vitesseInitiale, acceleration, temps float64) float64 {
	return vitesseInitiale*temps + 0.5*acceleration*temps*temps
}

// VitesseFinale: calcule la vitesse finale donnée la vitesse initiale, l'accélération et le temps.
// Utilise : v = vi + a * t
func VitesseFinale(vitesseInitiale, acceleration, temps float64) float64 {
	return vitesseInitiale + acceleration*temps
}
