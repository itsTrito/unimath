package unimath.tmp.display;

import javax.swing.*;
import java.awt.*;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

/**
 * The type Fenetre principale.
 */
public class FenetrePrincipale extends JFrame implements PropertyChangeListener {

	/**
	 * The constant serialVersionUID.
	 */
	private static final long serialVersionUID = 1L;
	/**
	 * The constant TITRE_FENETRE.
	 */
	private static final String TITRE_FENETRE = "Laboratoire 1 : LOG121 - Simulation";
	/**
	 * The constant DIMENSION.
	 */
	private static final Dimension DIMENSION = new Dimension(700, 700);

	/**
	 * The Panneau principal.
	 */
	private final PanneauPrincipal panneauPrincipal;

	/**
	 * Instantiates a new Fenetre principale.
	 */
	public FenetrePrincipale() {
		panneauPrincipal = new PanneauPrincipal(DIMENSION);
		MenuFenetre menuFenetre = new MenuFenetre();
		add(panneauPrincipal);
		add(menuFenetre, BorderLayout.NORTH);
		// Faire en sorte que le X de la fen�tre ferme la fen�tre
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setTitle(TITRE_FENETRE);
		setSize(DIMENSION);
		// Rendre la fen�tre visible
		setVisible(true);
		// Mettre la fen�tre au centre de l'�cran
		setLocationRelativeTo(null);
		// Empêcher la redimension de la fen�tre
		setResizable(false);
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		if (evt.getPropertyName().equals("state") || evt.getPropertyName().equals("refresh")) {
			if (evt.getPropertyName().equals("state") && evt.getNewValue() instanceof Paintable[]) {
				Paintable[] newPaintables = (Paintable[]) evt.getNewValue();
				panneauPrincipal.setPaintableElements(newPaintables);
			}
			repaint();
		}
	}
}
