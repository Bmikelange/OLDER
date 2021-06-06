package application;


public abstract class Entite implements Runnable{
	
	// la direction dans laquelle se deplace l'entit�
	public Direction CurrentDirection;
	
	//d�fini si l'entit� peu mourrir ou non
	public int immortal_object;
	
	//le type de l'entit�
	public int type;
	
	//la position pr�c�dente en x de l'entit�
	public int precedent_x;
	
	//la position pr�c�dente en y de l'entit�
	public int precedent_y;
	
	//la position en x de l'entit�
	public int position_x;
	
	//la position en y de l'entit�
	public int position_y;
	
	//une copie de la carte de jeu
	public Case[][] localTab;
	
	//un booleen de controlle pour arreter les thread
	public boolean cancel=false;
	
	//la vitesse d'une entit� (ici le temps de sleep d'un thread)
	public int vitesse;
	
	public void run()
	{	
	}
	
	//constructeur de la classe entite
	public Entite(Direction cur,int im,int ty,int posx,int posy, Case[][] tab)
	{
		CurrentDirection=cur;
		immortal_object=im;
		type=ty;
		position_x=posx;
		position_y=posy;
		localTab=tab;
		precedent_x=0;
		precedent_y=0;
		vitesse=300;
	}
	
	
	
	protected abstract void RealiserAction();
}
