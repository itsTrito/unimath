package unimath.tmp.controllers;



import javax.swing.*;

/**
 * Classe faisant le lien entre le contrôleur de simulation et l'interface utilisateur.
 * Contrôle la vitesse de la simulation et si elle est en marche.
 */
public class Environnement extends SwingWorker<Object, String> {
	/**
	 * The Actif.
	 */
	private boolean actif = true;
	/**
	 * The constant DELAI.
	 */
	private static final int DELAI = 10;

	/**
	 * Instantiates a new Environnement.
	 */
	public Environnement() {
	}
	
	@Override
	protected Object doInBackground() throws Exception {
		while(actif) {
			Thread.sleep(DELAI);
			firePropertyChange("refresh", null, "REFRESH");
		}
		return null;
	}
}