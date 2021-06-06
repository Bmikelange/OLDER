package application;

import java.io.File;
import java.io.IOException;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.SourceDataLine;
import javax.sound.sampled.UnsupportedAudioFileException;

public class Music implements Runnable{
	
	//chemin d'acces vers la musique
	String fullPath;
	
	//booleen de controle du thread
	public boolean flag;
	
	public Music(String path)
	{
		fullPath=path;
		flag=false;
	}
	
	//ouvres un fichier de musique et le lit sur la carte audio
	synchronized public void run()
	{
		//cree un flux audio à partir du fichier
		String musicPath=fullPath+"music.wav";
        File file=new File(musicPath);
        AudioInputStream audioInputStream = null;
        try{
             audioInputStream = AudioSystem.getAudioInputStream(file);

           } catch (UnsupportedAudioFileException e) {
               	e.printStackTrace();
                 return;
           } catch (IOException e) {
                   e.printStackTrace();
                   return;
           }
        
        //recupere le format et les infos de la musique
        AudioFormat audioFormat = audioInputStream.getFormat();
        
        DataLine.Info infom = new DataLine.Info(SourceDataLine.class,
               audioFormat);
        SourceDataLine line;
        try {
        line = (SourceDataLine) AudioSystem.getLine(infom);
                  
        } catch (LineUnavailableException e) {
          e.printStackTrace();
          return;
        }
        try {
        	line.open(audioFormat);
        } catch (LineUnavailableException e) {
        		e.printStackTrace();
        		return;
        }
        
        //lie le flux a la carte son
        line.start();
        
        //ecrit les données bytes a bytes de la musique sur la carte son
        try {
        	byte bytes[] = new byte[1024];
        	int bytesRead=0;
        	while (((bytesRead = audioInputStream.read(bytes, 0, bytes.length)) != -1)) {
        		if(flag==true)
        		{
        			flag=false;
        			break;
        		}
        		line.write(bytes, 0, bytesRead);
        	}
        } catch (IOException io) {
        	io.printStackTrace();
        	return;
        }
	}

}
