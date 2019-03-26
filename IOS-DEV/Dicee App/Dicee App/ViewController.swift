//
//  ViewController.swift
//  Dicee App
//
//  Created by ali mirabzadeh on 3/26/19.
//  Copyright © 2019 AMZ Development. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    let diceArr = ["dice1", "dice2", "dice3", "dice4", "dice5", "dice6"]
    var randomDice1: Int=0
    var randomDice2: Int=0
    //Dice1 variable
    @IBOutlet weak var dice1: UIImageView!
    //Dice2 variable
    @IBOutlet weak var dice2: UIImageView!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        updateDiceImage()
    }
    //roll button block
    @IBAction func rollButton(_ sender: UIButton)
    {
       updateDiceImage()
    }
    //detect motion shake so shaking the phone would roll the dice
    override func motionEnded(_ motion: UIEvent.EventSubtype, with event: UIEvent?)
    {
        updateDiceImage()
    }
    //function that update the dice images
    func updateDiceImage()
    {
        //create a random number from 0 to 5 and assign it to the variables randomDice1 and randomDice2
        randomDice1 = Int.random(in: 0 ... 5)
        randomDice2 = Int.random(in: 0 ... 5)
        //use dice1 and dice2 IBOutlet and use the 'image' method and UIImage data type to choose
        //a random dice '.png' from the asset
        dice1.image=UIImage.init(named: diceArr[randomDice1])
        dice2.image=UIImage.init(named: diceArr[randomDice2])
    }
}

