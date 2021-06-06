package application;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

public class Score {
	//	les scores sont stockés dans un fichier trié dans l'ordre décroissant.
    static String scoreFilePath = System.getProperty("user.dir") + File.separator+"PacManFx2"+ File.separator+"data"+ File.separator+"score.txt" ;
	
	private Score() {
	}
	
	public static void addScore(String name, int score) {
		try {
			ArrayList<String[]> scoreList = getScoreList();
			
			if(scoreList.isEmpty()) {
				scoreList.add(new String[] {name, Integer.toString(score)});
			}
			else {
				int i = 0;
				while(i < scoreList.size() && score <= Integer.parseInt(scoreList.get(i)[1])) {
					i++;
				}
				if(i == 10)
					return; //si le score est inferieur au 10eme score affiché, on quitte la méthode.
				if(scoreList.size() >= 10) 	
					scoreList.remove(9);
				
					scoreList.add(i, new String[] {name, Integer.toString(score)});
			}
			
			PrintWriter pw = new PrintWriter(scoreFilePath);

			int i=0;
			Iterator<String[]> itr = scoreList.iterator();
			while(itr.hasNext()) {
				String[] next = itr.next();
				pw.print(next[0]);
				pw.print(" ");
				pw.print(next[1]);
				if(i<scoreList.size()-1)
				{
					pw.print('\n');
				}
				i++;
			}
			pw.close();
			
		} catch (IOException e) {
			e.printStackTrace();
		}		
	}
	
	public static ArrayList<String[]> getScoreList() throws FileNotFoundException {
		ArrayList<String[]> scoreList = new ArrayList<String[]>();

		File file = new File(scoreFilePath);
		Scanner sc;
		sc = new Scanner(file);

		while(sc.hasNextLine()) {
			scoreList.add(new String[] {
					sc.next(),
					sc.next(),
			});
		}
		sc.close();


		return scoreList;		
	}
	
	
	public static void clearScores() throws IOException {
		PrintWriter pw = new PrintWriter(scoreFilePath);
		pw.close();
	}
	
}
