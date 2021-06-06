package application;
	
import application.*;
import javafx.animation.Animation;
import javafx.animation.Timeline;
import javafx.animation.KeyFrame;
import javafx.util.Duration;
import javafx.application.Application;
import java.io.*;
import javafx.stage.StageStyle;
import javafx.scene.transform.Rotate;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.MouseButton;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.Background;
import javafx.scene.control.CheckBox;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;


import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.geometry.HPos;
import javafx.geometry.VPos;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.Node;
import javafx.scene.effect.Blend;
import javafx.scene.effect.BlendMode;
import javafx.scene.effect.ColorInput; 
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.event.ActionEvent;

import javafx.scene.input.KeyEvent;
import javafx.scene.shape.Rectangle;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import javafx.scene.text.Text;
import java.util.Observable;
import java.util.Observer;

import javafx.scene.control.Button;

public class Main extends Application{
	
	//position en x de la fenetre d'affichage
	double initialX;
	
	//position en y de la fenetre d'affichage
	double initialY;
	
	//image de la pacgomme
	Image imageA;
	
	//image des murs
	Image imageMur;
	
	//image du sol
	Image imageSol;
	
	//image de la superpacgomme
	Image imageB;
	
	//image de font du menu
	Image imageMenu;
	
	//defini si le son est actif ou non
	boolean sounds=true;
	
	//le tableau de jeu(affichage)
	GridPane table;
	
	//le temps et les actions avant que le pacman se reinitialise 
	//apres avoir mange une super pac gomme
	Timeline timeline;
	
	//les images des entitées
	ImageView[] selectedImage;
	
	//le texte de fin de partie
	Text label;
	
	//le rectangle sur lequel est affiché le texte de fin de partie
	Rectangle regfin;
	
	//l'effet applique quand pacman mange une superpacgomme
	Blend blend;
	
	//le texte du score du joueur
	Text score;
	
	//le rectangle sur lequel est affiché le texte du score du joueur
	Rectangle regScore;
	
	//le controlleur qui lie la vue et le modele
	Controller contr;
	
	//le chemin d'acces aux images/music
	String fullPath;
	
	//le thread qui execute les musiques
	Thread tMusic;
	
	//le temps avant chaque nouveau lancement de musique
	Timeline sound;
	
	//un lecteur de musique
	Music lecteur;
	
	//le modele de jeu
	Jeu game;
	
	//aleatoire ou non
	boolean setalea=false;
	
	
	//initialise l'affichage du plateau de jeu
	public void initialise(GridPane table,Jeu game)
	{
		for(int i=0;i<21;i++)
		{
			for(int j=0;j<21;j++)
			{	
				StackPane pane=new StackPane();
				if(game.tableauJeu[i][j].values==1)
				{
					ImageView reg=new ImageView();
		        	reg.setImage(imageMur);
			        reg.setFitHeight(20);
			        reg.setFitWidth(20);
					pane.getChildren().add(reg);
				}
				if(game.tableauJeu[i][j].values==0)
				{
					ImageView sol=new ImageView();
					sol.setImage(imageSol);
			        sol.setFitHeight(20);
			        sol.setFitWidth(20);
					pane.getChildren().add(sol);
					if(game.tableauJeu[i][j].PacGomme==true)
					{
						ImageView reg=new ImageView();
			        	reg.setImage(imageA);
				        reg.setFitHeight(10);
				        reg.setFitWidth(10);
						pane.getChildren().add(reg);
					}
					if(game.tableauJeu[i][j].SupPacGomme==true)
					{
						ImageView reg=new ImageView();
						reg.setImage(imageB);
				        reg.setFitHeight(20);
				        reg.setFitWidth(20);
						pane.getChildren().add(reg);
					}
				}
				pane.setMinSize(20, 20);
				pane.setMaxSize(20, 20);
				pane.setAlignment(Pos.CENTER);
				table.add(pane,i,j,1,1);
			}
		}
	}
	
	//active l'effet visuel de la superpacgomme
	public void effecton(GridPane table,Blend blend)
	{
		table.setEffect(blend);
	}
	
	//desactive l'effet visuel de la superpacgomme
	public void effectof(GridPane table)
	{
		table.setEffect(null);
	}
	
	@Override
	public void start(Stage primaryStage) {
		try {
			GridPane root;
			contr=new Controller();
			game= new Jeu();
			
			//trouves le chemin d'acces à tous les fichiers
			String currentWorkingPath = System.getProperty("user.dir");
	        fullPath = currentWorkingPath  + File.separator+"PacManFx2"+ File.separator+"data"+ File.separator;
	        
	        //objet de type lecteur de musique
	        lecteur=new Music(fullPath);
	        //thread gerant la musique
	        tMusic=new Thread(lecteur);
	        
	        //texte informatif
	        Text info=new Text("press esc to quit, shift to minimize\n H to activate/desactivate sound");
	        
	        //repete la musique à l'infini
	        sound=new Timeline(new KeyFrame(Duration.millis(4300),ev -> { Thread tMusic1=new Thread(lecteur);
	        	tMusic1.start();}));
	        sound.setCycleCount(Animation.INDEFINITE);
	        
	        //charge toutes les images affichable
	        imageMenu=new Image(new FileInputStream(fullPath+"font.jpg"));
			Image imEntete=new Image(new FileInputStream(fullPath+"entete.jpg"));
			Image imButton=new Image(new FileInputStream(fullPath+"player.png"));
			Image imButtonR=new Image(new FileInputStream(fullPath+"return.png"));
			Image imButtonS=new Image(new FileInputStream(fullPath+"board.png"));
			try {
				imageSol=new Image(new FileInputStream(fullPath+"sol.jpg"));
	        	}catch(Exception e) {
	        	}
			try {
				imageMur=new Image(new FileInputStream(fullPath+"mur.jpg"));
	        	}catch(Exception e) {
	        	}
			
			try {
				imageA = new Image(new FileInputStream(fullPath+"pacgomme.png"));
				
			} catch (FileNotFoundException e) {
			}
			try {
				imageB = new Image(new FileInputStream(fullPath+"Gold.png"));
				
			} catch (FileNotFoundException e) {
			}
			
			final ImageView Entete =new ImageView();
	        Entete.setImage(imEntete);
	        Entete.setFitHeight(120);
	        Entete.setFitWidth(26*20);
	        final ImageView Button1 =new ImageView();
	        Button1.setImage(imButton);
	        Button1.setFitHeight(80);
	        Button1.setFitWidth(16*20);
	        final ImageView Button2 =new ImageView();
	        Button2.setImage(imButtonS);
	        Button2.setFitHeight(80);
	        Button2.setFitWidth(16*20);
	        final ImageView Button3 =new ImageView();
	        Button3.setImage(imButtonR);
	        Button3.setFitHeight(20);
	        Button3.setFitWidth(20);
	        
	        //défini le nom et l'icone du jeu
	        primaryStage.setTitle("PacMan");
	        primaryStage.initStyle(StageStyle.UNDECORATED); 
	        primaryStage.getIcons().setAll(new Image(new FileInputStream(fullPath+"icon.jpg")));
	        
	        //crée l'effet affiché quand on ramasse une super pac gomme
			blend = new Blend();
			blend.setMode(BlendMode.COLOR_BURN);
			ColorInput colorInput = new ColorInput();
			colorInput.setPaint(Color.STEELBLUE);
			colorInput.setX(0);
			colorInput.setY(0);
			colorInput.setWidth(20*21);
			colorInput.setHeight(20*21);
			blend.setTopInput(colorInput);
			
			//crée l'affichage principale
			root = new GridPane();
			int k=0;
			Rectangle[] reg=new Rectangle[4];
			for(int i=1;i<4;i=i+2)
			{
				for(int j=1;j<4;j=j+2)
				{
					reg[k] =new Rectangle(50,50,Color.LIGHTGREY);
					root.add(reg[k], i, j,1,1);
					k++;
				}
			}
			
			k=0;
			Rectangle[] regDec=new Rectangle[4];
			for(int i=0;i<5;i=i+4)
			{
				regDec[k] =new Rectangle(5,32*20+5,Color.BLACK);
				root.add(regDec[k], i, 0,1,4);
				k++;
			}
			Rectangle regBas=new Rectangle(26*20+10,5,Color.BLACK);
			root.add(regBas,0, 4,5,1);
			root.add(Entete, 1, 0,3,1);
			root.add(info, 2, 3,1,1);
	        root.setHalignment(info,HPos.CENTER);
			
			//initialise la scène d'affichage
			Scene scene = new Scene(root,26*20+10,32*20+5,Color.WHITE);
			scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
	        
			//bouton de menu
			Button playerB =new Button();
			playerB.setGraphic(Button1);
			playerB.setStyle("-fx-padding:1;-fx-border-style:none;-fx-border-width:0;-fx-border-insets:0;"); 
			playerB.setOnAction(new EventHandler<ActionEvent>() {
			   @Override 
			   public void handle(ActionEvent e) {
				   root.getChildren().remove(table);
				   game_launcheur(root,primaryStage);
			   }});
			Button BoardB =new Button();
			BoardB.setGraphic(Button2);
			BoardB.setStyle("-fx-padding:1;-fx-border-style:none;-fx-border-width:0;-fx-border-insets:0;"); 
			BoardB.setOnAction(new EventHandler<ActionEvent>() {
			   @Override 
			   public void handle(ActionEvent e) {
				   root.getChildren().remove(table);
				   GridPane tempo=new GridPane();
				   StackPane joli=new StackPane();
				   joli.setMinSize(90, 20);
				   joli.setMaxSize(90, 20);
				   Button returnB=new Button("MENU",Button3);
				   returnB.setStyle("-fx-background-color: transparent;-fx-border-color: black;");
				   returnB.setOnAction(new EventHandler<ActionEvent>() {
					@Override
					public void handle(ActionEvent e)
					{
						root.getChildren().remove(tempo);
						root.getChildren().remove(joli);
						menu_launcheur(root,playerB,BoardB);
				   }});
				   tempo.setMinSize(21*20, 21*20);
				   tempo.setMaxSize(21*20, 21*20);
				   tempo.setBackground(new Background(new BackgroundFill(Color.BLACK,CornerRadii.EMPTY,Insets.EMPTY)));
				   try {
					   game.initscoretab();
					   } catch (IOException e1) {
					   e1.printStackTrace();
					   }
				   StackPane joli2=new StackPane();
				   joli2.setMinSize(50, 120);
				   joli2.setMaxSize(50, 120);
				   tempo.add(joli2,0,0);
				   Text text= new Text("LEADERBOARD");
				   text.setFont(new Font("Verdana",40));
			       text.setFill(Color.WHITE);
				   tempo.add(text, 1, 0);
				   for(int i=0;i<game.scoreTab.size();i++)
				   {
					   Text affichage=new Text((i+1)+" "+game.scoreTab.get(i)[0]+" "+game.scoreTab.get(i)[1]);
					   affichage.setFont(new Font("Verdana",20));
				       affichage.setFill(Color.color(Math.random(),Math.random(),Math.random()));
				       tempo.add(affichage,1,i+1);
				       tempo.setHalignment(affichage, HPos.CENTER);
				   }
				   root.add(joli,2, 1);
				   joli.getChildren().add(returnB);
				   root.add(tempo,2,2,1,1);
			   }});
			
			menu_launcheur(root,playerB,BoardB);
			
	        // actions effectuées sur le menu
	        root.setOnKeyPressed(new EventHandler<KeyEvent>() {
				@Override 
   		         public void handle(KeyEvent e) {
					switch (e.getCode())
   		        	 {
   		        	 	case ESCAPE:
		        	 		System.exit(0);
		        	 		break;
   		        	 	case SHIFT:
   		        	 		primaryStage.setIconified(true);
   		        	 		break;
   		        	 }
   		         } 
	        });
			
	        //sauvegarde la position actuelle du stage
	        root.setOnMousePressed(new EventHandler<MouseEvent>() {
	            @Override
	            public void handle(MouseEvent me) {
	                if(me.getButton()!=MouseButton.MIDDLE)
	                {
	                    initialX = me.getSceneX();
	                    initialY = me.getSceneY();
	                }
	                else
	                {
	                    root.getScene().getWindow().centerOnScreen();
	                    initialX = root.getScene().getWindow().getX();
	                    initialY = root.getScene().getWindow().getY();
	                }

	            }
	       });
	        
	       //modifie la position du stage
	       root.setOnMouseDragged(new EventHandler<MouseEvent>() {
	            @Override
	            public void handle(MouseEvent me) {
	                if(me.getButton()!=MouseButton.MIDDLE)
	                {
	                    root.getScene().getWindow().setX( me.getScreenX() - initialX );
	                    root.getScene().getWindow().setY( me.getScreenY() - initialY);
	                }
	            }
	        });
	        primaryStage.setScene(scene);
			primaryStage.show();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	//fonction menu
	public void menu_launcheur(GridPane root,Button playerB,Button BoardB)
	{
		table= new GridPane();
		ImageView font=new ImageView();
		Pane plusjoli=new Pane();
		plusjoli.setMinSize(50, 60);
		plusjoli.setMaxSize(50, 60);
		Pane plusjoli2=new Pane();
		plusjoli2.setMinSize(30, 60);
		plusjoli2.setMaxSize(30, 60);
		font.setImage(imageMenu);
        font.setFitHeight(21*20);
        font.setFitWidth(21*20);
        CheckBox aleacheck=new CheckBox("niveau aleatoire");
        aleacheck.setStyle("-fx-text-fill: white");
        aleacheck.selectedProperty().addListener(new ChangeListener<Boolean>() {
            public void changed(ObservableValue<? extends Boolean> ov,
                    Boolean old_val, Boolean new_val) {
                        setalea= !setalea;
            }});
        table.add(plusjoli, 0, 0);
        table.add(plusjoli2, 0, 19);
        table.add(font, 0, 0,21,21);
        table.add(playerB,7,7);
        table.add(BoardB, 7, 20);
        table.add(aleacheck, 7, 10);
        root.add(table,2,2,1,1);
	}
	
	//fonction de jeu
	public void game_launcheur(GridPane root,Stage primaryStage)
	{
		sound.play();
		tMusic.start();
		//crée et initialise les éléments du modèle
		try {
			contr.init(game);
			} catch (IOException e2) {
			e2.printStackTrace();
			}
		
		//crée et initialise la grille
		table= new GridPane();
		initialise(table,game);
		
		
		//crée le timer quand le pac man a mangé la pacgomme
		timeline = new Timeline(new KeyFrame(
		        Duration.millis(5000),
		        ae -> contr.reset(table,game)));
		timeline.getKeyFrames().addAll(
	            new KeyFrame(Duration.millis(3400), ae -> effectof(table)),
	            new KeyFrame(Duration.millis(3600), ae -> effecton(table,blend)),
	            new KeyFrame(Duration.millis(3800), ae -> effectof(table)),
	            new KeyFrame(Duration.millis(4000), ae -> effecton(table,blend)),
	            new KeyFrame(Duration.millis(4200), ae -> effectof(table)),
	            new KeyFrame(Duration.millis(4400), ae -> effecton(table,blend)),
	            new KeyFrame(Duration.millis(4600), ae -> effectof(table)),
	            new KeyFrame(Duration.millis(4800), ae -> effecton(table,blend))
	        ); 
		
		//crée et initialise les affichages des pacmans et fantomes
		selectedImage = new ImageView[5];
        Image[] image1= new Image[5];
        for(int i=0;i<5;i++)
        {
        	String Path=fullPath+"pacman"+i+".png";
        	selectedImage[i]=new ImageView();
        	try {
        		image1[i]=new Image(new FileInputStream(Path));
        		} catch (FileNotFoundException e1) {
        		e1.printStackTrace();
        		}
        	selectedImage[i].setImage(image1[i]);
	        selectedImage[i].setFitHeight(20);
	        selectedImage[i].setFitWidth(20);
        }
        
        //initialise le texte de fin
        label= new Text();
        label.setFont(new Font("Verdana",40));
        regfin=new Rectangle(21*20,40,Color.BLACK);
        
        //texte de score
        score=new Text();
        score.setFont(new Font("Verdana",20));
        score.setFill(Color.RED);
        regScore=new Rectangle(21*3,20,Color.BLACK);
        
        //ajoutes tous les éléments créé a l'affichage principal
        root.add(table,2,2,1,1);
        root.add(regScore, 2, 1,1,1);
        
        // lances l'execution des fantomes par des threads
        contr.lances(game);
        Thread Tjeu=new Thread(game);
        Tjeu.start();
        
      //initialise le bouton de pause
		Button restartButton =new Button("the game is paused, click on me to restart");
	       restartButton.setOnAction(new EventHandler<ActionEvent>() {
			   @Override 
			   public void handle(ActionEvent e) {
		 				root.getChildren().remove(restartButton);
		 				Thread tMusic2=new Thread(lecteur);
	        	 		tMusic2.start();
		 				sound.play();
		 				game.fin=false;
		 				Thread Tjeu1=new Thread(game);
	    				Tjeu1.start();
	    				contr.lances(game);
			    	}
			    });
        
        //crée le bouton de restart
		Button B=new Button("restart");
		B.setOnAction(new EventHandler<ActionEvent>() {
		    @Override public void handle(ActionEvent e) {
		    	timeline.stop();
		    	root.getChildren().remove(table);
		    	table=new GridPane();
        		contr.reset(table,game);
		    	game.fin=true;
		        if(root.getChildren().contains(label)==true)
		        {
		        	root.getChildren().remove(label);
		        	root.getChildren().remove(regfin);
		        	if(sounds==true)
		        	{
		        		lecteur.flag=false;
		        	}
		        }
		        else
		        {
		        	if(sounds==true)
		        	{
		        		lecteur.flag=true;
		        	}
		        }
		        if(root.getChildren().contains(restartButton)==true)
		        {
		        	root.getChildren().remove(restartButton);
		        	if(sounds==true)
		        	{
		        		lecteur.flag=false;
		        	}
		        }
		    	contr.stopJeu(game);
		    	if(setalea)
		    	{
			    	try {
			    		contr.initalea(game);
			    	}catch(Exception ex) {
						ex.printStackTrace();
					}
		    	}
		    	else
		    	{
		    		try {
			    		contr.init(game);
			    	}catch(Exception ex) {
						ex.printStackTrace();
					}
		    	}
		        initialise(table,game);
		        if(sounds==true)
		        {
		        	Thread tMusic2=new Thread(lecteur);
        	 		tMusic2.start();
        	 		try {  
        	            Thread.sleep(300) ;
        	         }  catch (InterruptedException eex) {
        	         }
		        	sound.play();
		        }
		        root.add(table,2,2,1,1);
		        contr.lances(game);
		        game.fin=false;
 				Thread Tjeu1=new Thread(game);
				Tjeu1.start();
		    }
		});
		root.add(B,2,1,1,1);
		root.setHalignment(B,HPos.CENTER);
        
        //détecte si une touche est pressée et effectue l'action indiquée
        root.setOnKeyPressed(new EventHandler<KeyEvent>() {
			@Override 
		     public void handle(KeyEvent e) {
				contr.apply(e.getCode(), game);
				switch (e.getCode())
		        	 {
		        	 	case UP:
		        	 		selectedImage[0].getTransforms().clear();
		        	 		final Rotate rotate = new Rotate(270,10,10); 
		        	 		selectedImage[0].getTransforms().add(rotate);
		        	 		break;
		        	 	case DOWN:
		        	 		game.jeuPacman(Direction.Bas);
		        	 		selectedImage[0].getTransforms().clear();
		        	 		final Rotate rotate1 = new Rotate(90,10,10); 
		        	 		selectedImage[0].getTransforms().add(rotate1);
		        	 		break;
		        	 	case LEFT:
		        	 		game.jeuPacman(Direction.Gauche);
		        	 		selectedImage[0].getTransforms().clear(); 
		        	 		selectedImage[0].setScaleX(-1);
		        	 		break;
		        	 	case RIGHT:
		        	 		game.jeuPacman(Direction.Droite);
		        	 		selectedImage[0].getTransforms().clear();
		        	 		selectedImage[0].setScaleX(1);
		        	 		break;	
		        	 	case ESCAPE:
	        	 		System.exit(0);
	        	 		break;
		        	 	case SHIFT:
			        	 	game.fin=true;
	   		        	 	sound.stop();
		        	 		lecteur.flag=true;
		        	 		contr.stopJeu(game);
		        	 		if(root.getChildren().contains(regfin)==false)
		        	 		{
			        	 		root.add(restartButton,2,2,1,1);
			        	 		root.setHalignment(restartButton,HPos.CENTER);
		        	 		}
			        	 		primaryStage.setIconified(true);
		        	 		break;
		        	 	case H:
		        	 		if(sounds==true)
		        	 		{
   		        	 		sound.stop();
   		        	 		lecteur.flag=true;
   		        	 		sounds=false;
		        	 		}
		        	 		else
		        	 		{
		        	 			Thread tMusic2=new Thread(lecteur);
		        	 			tMusic2.start();
		        	 			sound.play();
		        	 			sounds=true;
		        	 		}
		        	 }
		         } 
        });
       
       Observer obs=new Observer() {
            
            @Override
            public void update(Observable o, Object arg) {
            	if(root.getChildren().contains(score)==true)
        		{
        			root.getChildren().remove(score);
        		}
        		
        		score.setText(Integer.toString(game.score));
        		root.add(score, 2, 1,1,1);
        		for (Node node : table.getChildren()) {
        		    if (node instanceof StackPane
        		     && table.getColumnIndex(node) ==game.tableauEntite[0].position_y 
        		     && table.getRowIndex(node) == game.tableauEntite[0].position_x) {
        		    	if(((StackPane)node).getChildren().size()==2)
        		    	{
        		    		((StackPane)node).getChildren().remove(1);
        		    	}
        		    }
        		}
        		for(int i=0;i<5;i++)
            	{
                	if(table.getChildren().contains(selectedImage[i])==true)
                	{
                		table.getChildren().remove(selectedImage[i]);
                	}
            		table.add(selectedImage[i],game.tableauEntite[i].position_y,game.tableauEntite[i].position_x,1,1);
            	}
            	int finJeu=game.Vic;
            	if(finJeu==1)
            	{		    
            		label.setText("YOU WIN !!");
            		label.setFill(Color.RED);
            		if(root.getChildren().contains(regfin))
            		{
            			root.getChildren().remove(regfin);
            		}
            		if(root.getChildren().contains(label))
            		{
            			root.getChildren().remove(label);
            		}
            		root.getChildren().remove(table);
            		table=new GridPane();
            		table.setMinSize(21*20, 21*20);
  				   	table.setMaxSize(21*20, 21*20);
  				   	table.setBackground(new Background(new BackgroundFill(Color.BLACK,CornerRadii.EMPTY,Insets.EMPTY)));
            		TextField text=new TextField();
            		text.setPromptText("click and write your name");
            		Button button=new Button("valider");
            		button.setOnAction(new EventHandler<ActionEvent>() {
            			@Override
            			public void handle(ActionEvent e)
            			{
            				if((text.getText() != null) && (!text.getText().isEmpty()))
            						{
            							Score.addScore(text.getText(), game.score);
            							root.getChildren().remove(regfin);
            							root.getChildren().remove(label);
            							root.getChildren().remove(button);
            							root.getChildren().remove(text);
            							try {
            								   game.initscoretab();
            								   } catch (IOException e1) {
            								   e1.printStackTrace();
            								   }
            							   StackPane joli2=new StackPane();
            							   joli2.setMinSize(50, 120);
            							   joli2.setMaxSize(50, 120);
            							   table.add(joli2,0,0);
            							   Text text= new Text("LEADERBOARD");
            							   text.setFont(new Font("Verdana",40));
            						       text.setFill(Color.WHITE);
            							   table.add(text, 1, 0);
            							   for(int i=0;i<game.scoreTab.size();i++)
            							   {
            								   Text affichage=new Text((i+1)+" "+game.scoreTab.get(i)[0]+" "+game.scoreTab.get(i)[1]);
            								   affichage.setFont(new Font("Verdana",20));
            							       affichage.setFill(Color.color(Math.random(),Math.random(),Math.random()));
            							       table.add(affichage,1,i+1);
            							       table.setHalignment(affichage, HPos.CENTER);
            							   }
            						}
            			}
            		});
  				   	root.add(table, 2, 2);
  				   	root.add(text,2, 2);
  				   	root.add(button,2,2);
            		root.add(regfin, 2, 2,1,1 );
            		root.add(label, 2, 2,1,1);
            		root.setHalignment(label,HPos.CENTER);
            		root.setValignment(label,VPos.TOP);
            		root.setHalignment(button,HPos.CENTER);
            		root.setValignment(button,VPos.BOTTOM);
            		root.setValignment(regfin,VPos.TOP);
            		lecteur.flag=true;
            		sound.stop();
            		timeline.stop();
            		contr.reset(table,game);
            		game.fin=true;
            		contr.stopJeu(game);
            	}
            	if(finJeu==2)
            	{
            		label.setText("YOU LOSE !!");
            		label.setFill(Color.RED);
            		if(root.getChildren().contains(regfin))
            		{
            			root.getChildren().remove(regfin);
            		}
            		if(root.getChildren().contains(label))
            		{
            			root.getChildren().remove(label);
            		}
            		root.add(regfin, 2, 2,1,1 );
            		root.add(label, 2, 2,1,1);
            		root.setHalignment(label,HPos.CENTER);
            		lecteur.flag=true;
            		sound.stop();
            		game.fin=true;
            		contr.stopJeu(game);
            	}
            	if(finJeu==3)
            	{
            		table.setEffect(blend);
            		contr.ralentiF(game);
            		timeline.play();
            	}
        	}
        };
        game.addObserver(obs);
   }
	
	
	public static void main(String[] args) {
		launch(args);
	}
}
