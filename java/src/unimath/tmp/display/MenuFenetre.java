package unimath.tmp.display;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.event.ActionEvent;
import java.io.File;
import java.nio.file.FileSystems;

/**
 * The type Menu fenetre.
 */
public class MenuFenetre extends JMenuBar {

	/**
	 * The constant serialVersionUID.
	 */
	private static final long serialVersionUID = 1L;
	/**
	 * The constant MENU_FICHIER_TITRE.
	 */
	private static final String MENU_FICHIER_TITRE = "Fichier";
	/**
	 * The constant MENU_FICHIER_CHARGER.
	 */
	private static final String MENU_FICHIER_CHARGER = "Charger";
	/**
	 * The constant MENU_FICHIER_QUITTER.
	 */
	private static final String MENU_FICHIER_QUITTER = "Quitter";
	/**
	 * The constant MENU_SIMULATION_TITRE.
	 */
	private static final String MENU_SIMULATION_TITRE = "Simulation";
	/**
	 * The constant MENU_SIMULATION_CHOISIR.
	 */
	private static final String MENU_SIMULATION_CHOISIR = "Choisir";
	/**
	 * The constant MENU_AIDE_TITRE.
	 */
	private static final String MENU_AIDE_TITRE = "Aide";
	/**
	 * The constant MENU_AIDE_PROPOS.
	 */
	private static final String MENU_AIDE_PROPOS = "À propos de...";

	/**
	 * Instantiates a new Menu fenetre.
	 */
	public MenuFenetre() {
		ajouterMenuFichier();
		ajouterMenuSimulation();
		ajouterMenuAide();
	}

	/**
	 * Cr�er le menu de Fichier
	 */
	private void ajouterMenuFichier() {
		JMenu menuFichier = new JMenu(MENU_FICHIER_TITRE);
		JMenuItem menuCharger = new JMenuItem(MENU_FICHIER_CHARGER);
		JMenuItem menuQuitter = new JMenuItem(MENU_FICHIER_QUITTER);

		menuCharger.addActionListener((ActionEvent e) -> {
			JFileChooser fileChooser = new JFileChooser(FileSystems.getDefault().getPath(".").toFile());
			fileChooser.setDialogTitle("Sélectionnez un fichier de configuration");
			fileChooser.setAcceptAllFileFilterUsed(false);
			// Cr�er un filtre
			FileNameExtensionFilter filtre = new FileNameExtensionFilter(".xml", "xml");
			fileChooser.addChoosableFileFilter(filtre);

			int returnValue = fileChooser.showOpenDialog(null);

			if (returnValue == JFileChooser.APPROVE_OPTION) {
				File selectedFile = fileChooser.getSelectedFile();
			}
		});

		menuQuitter.addActionListener((ActionEvent e) -> {
			System.exit(0);
		});

		menuFichier.add(menuCharger);
		menuFichier.add(menuQuitter);

		add(menuFichier);

	}

	/**
	 * Cr�er le menu de Simulation
	 */
	private void ajouterMenuSimulation() {
		JMenu menuSimulation = new JMenu(MENU_SIMULATION_TITRE);
		JMenuItem menuChoisir = new JMenuItem(MENU_SIMULATION_CHOISIR);
		menuSimulation.add(menuChoisir);

		menuChoisir.addActionListener((ActionEvent e) -> {
		});
		add(menuSimulation);

	}

	/**
	 * Cr�er le menu Aide
	 */
	private void ajouterMenuAide() {
		JMenu menuAide = new JMenu(MENU_AIDE_TITRE);
		JMenuItem menuPropos = new JMenuItem(MENU_AIDE_PROPOS);
		menuAide.add(menuPropos);

		menuPropos.addActionListener((ActionEvent e) -> {
			JOptionPane.showMessageDialog(null,
					"<html><p>Application simulant une chaine de production d'avions.</p>" + "<br>"
							+ "<p>&copy; &nbsp; 2017 &nbsp; Ghizlane El Boussaidi</p>"
							+ "<p>&copy; &nbsp; 2017 &nbsp; Dany Boisvert</p>"
							+ "<p>&copy; &nbsp; 2017 &nbsp; Vincent Mattard</p>" + "<br>"
							+ "<p>&Eacute;cole de technologie sup&eacute;rieure</p></html>");
		});
		add(menuAide);
	}

}
