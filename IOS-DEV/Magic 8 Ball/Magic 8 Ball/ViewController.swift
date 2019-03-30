//
//  ViewController.swift
//  Magic 8 Ball
//
//  Created by ali mirabzadeh on 3/26/19.
//  Copyright © 2019 AMZ Development. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    let ballArr = ["ball1", "ball2" , "ball3", "ball4" ,"ball5"]
    var randomBallImage : Int=0
    
    @IBOutlet weak var ballImage: UIImageView!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    //Ask button that will generate the random image
    @IBAction func askButton(_ sender: UIButton)
    {
        updateMagicBall()
    }
    //shake detector so that the app would generate a new magic ball
    override func motionEnded(_ motion: UIEvent.EventSubtype, with event: UIEvent?) {
        updateMagicBall()
    }
    func updateMagicBall ()
    {
        //generate a new random number between 0 and 4
        randomBallImage  = Int.random(in: 0 ... 4)
        //use image method for the ballImage to use the random number to load a new image from the asset
        ballImage.image=UIImage.init(named: ballArr[randomBallImage])
    }
}

