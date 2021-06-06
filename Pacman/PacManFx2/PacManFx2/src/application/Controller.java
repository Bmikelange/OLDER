package application;
import java.io.IOException;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.GridPane;


public class Controller {
	
	//dis au jeu de s'initialiser
	public void init(Jeu game) throws IOException
	{
		game.initialiser();
		
	}
	
	//dis au jeu de s'initialiser aleatoirement
	public void initalea(Jeu game)
	{
		game.niveau_aleatoire();
	}
	
	//dis au jeu de lancer les threads
	public void lances(Jeu game)
	{
		game.jeuFantome();
	}
	
	//envoie au pacman les touches cliquées
	public void apply(KeyCode e,Jeu game)
	{
		switch (e)
      	 {
      	 	case UP:
      	 		game.jeuPacman(Direction.Haut);
      	 		break;
      	 	case DOWN:
      	 		game.jeuPacman(Direction.Bas);
      	 		break;
      	 	case LEFT:
      	 		game.jeuPacman(Direction.Gauche);
      	 		break;
      	 	case RIGHT:
      	 		game.jeuPacman(Direction.Droite);
      	 		break;	
      	 	case ESCAPE:
      	 		game.canceljeuFantome();
      	 		break;
      	 	case SHIFT:
	        	 	game.canceljeuFantome();
      	 		break;
      	 }
	}
	
	//ralenti les fantomes
	public void ralentiF(Jeu game)
	{
		for(int i=1;i<5;i++)
		{
			game.tableauEntite[i].vitesse=500;
		}
	}
	
	//reset les effets de la superpacgomme
	public void reset(GridPane table,Jeu game)
	{
		table.setEffect(null);
		game.game_res();
		
	}
	
	//arretes les threads des fantomes
	public void stopJeu(Jeu game)
	{
		game.canceljeuFantome();
	}
}
