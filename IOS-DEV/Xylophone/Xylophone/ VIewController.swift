//
//  ViewController.swift
//  Xylophone
//
//  Created by Angela Yu on 27/01/2016.
//  Copyright © 2016 London App Brewery. All rights reserved.
//

import UIKit
//for audio
import AVFoundation

class ViewController: UIViewController, AVAudioPlayerDelegate{
    
    
    var audioPlayer : AVAudioPlayer!
     var soundSelected: String = ""
    let soundArr = ["note1", "note2", "note3", "note4", "note5", "note6" , "note7"]
    override func viewDidLoad() {
        super.viewDidLoad()
    }
    //all the 7 button would use this UIButton
    @IBAction func notePressed(_ sender: UIButton)
    {
        //sender.tag is the presses button
        //so depending on the which button has been pressed the corresponding note from the array
        soundSelected = soundArr[sender.tag-1]
        playSoundFunc()
    }
    //function that read the sounds from the sound file and play them depending on which button has been pressed
    func playSoundFunc( )
    {
        let soundURL = Bundle.main.url(forResource: soundSelected, withExtension: "wav")!
        do
        {
            audioPlayer = try AVAudioPlayer(contentsOf: soundURL)
            guard let player = audioPlayer else { return }
            
            player.prepareToPlay()
            player.play()
            
        }
            //catch error
        catch let error as NSError {
            print(error.description)
        }
    }
    
  

}

