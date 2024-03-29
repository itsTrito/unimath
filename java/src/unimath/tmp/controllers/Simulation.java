package unimath.tmp.controllers;

import unimath.tmp.display.FenetrePrincipale;

/**
 * Point d'entrée de la simulation.
 */
public class Simulation {

	/**
	 * Cette classe repr�sente l'application dans son ensemble.
	 *
	 * @param args the input arguments
	 */
	public static void main(String[] args) {
		Environnement environnement = new Environnement();
		FenetrePrincipale fenetre = new FenetrePrincipale();

		environnement.addPropertyChangeListener(fenetre);
		environnement.execute();
	}

}
