package unimath.tmp.display;

import javax.swing.*;
import java.awt.*;

/**
 * The type Panneau principal.
 */
public class PanneauPrincipal extends JPanel {

	/**
	 * The constant serialVersionUID.
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * The Paintable elements.
	 */
	private Paintable[] paintableElements;

	/**
	 * Instantiates a new Panneau principal.
	 *
	 * @param dimension the dimension
	 */
	public PanneauPrincipal(Dimension dimension) {
	}

	/**
	 * Sets paintable elements.
	 *
	 * @param paintables the paintables
	 */
	public void setPaintableElements(Paintable[] paintables) {
		this.paintableElements = paintables;
	}

	@Override
	public void paint(Graphics g) {
		super.paint(g);

		if (paintableElements != null) {
			for (Paintable p : paintableElements) {
				p.paint(g);
			}
		}
	}

}