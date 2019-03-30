//
//  ViewController.swift
//  Quizzler
//
//  Created by ali mirabzadeh on 3/26/19.

//

import UIKit

class ViewController: UIViewController {
    
    //Place your instance variables here
    
    //create the question bank
    let questionBank = QuestionBank()
    var pickedAns : Bool = false
    var questionNumber: Int=0
    var scoreCounter: Int=0
    @IBOutlet weak var questionLabel: UILabel!
    @IBOutlet weak var scoreLabel: UILabel!

    @IBOutlet weak var progressLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        nextQuestion()
    }
    //button function
    @IBAction func answerPressed(_ sender: AnyObject)
    {
        //if the True button is pressed
        if sender.tag == 1
        {
            //the picked answer would be set true
            pickedAns=true
        }
        //if the false button is chose
        else
        {
            //the set answer  would be set to false
            pickedAns=false
        }
        checkAnswer()
        questionNumber+=1
        nextQuestion()
    }
    //update the
    func updateUI()
    {
        //store the updated score in scoreLabel, since scorecounter is int, it should be converted to
        //string with "\()"
        scoreLabel.text = "Score: \(scoreCounter)"
        //keeps track of the question number
        progressLabel.text = "\(questionNumber+1)/13"
    }
    

    func nextQuestion()
    {
        if questionNumber <= 12
        {
            //load the next question on the label
            questionLabel.text = questionBank.list[questionNumber].question
            updateUI()
        }
        else
        {
            //pop-up alert
            let uiAlert = UIAlertController(title: "Awesome!", message: "The game is over! Do you want to take it again", preferredStyle: .alert )
            //pop-alert action
            let restartAction = UIAlertAction(title: "Restart", style: .default) { (UIAlertAction) in
                self.startOver()
            }
            //action for the pop-up
            uiAlert.addAction(restartAction)
            //present the alert to the viewer, does nothing after completion
            present(uiAlert, animated: true, completion: nil)
        }
    }
    //
    func checkAnswer()
    {
        //store the correct answer
        let correctAns = questionBank.list[questionNumber].answer
        if correctAns == pickedAns
        {
            scoreCounter = scoreCounter + 1
            //Used from -> https://github.com/relatedcode/ProgressHUD
            ProgressHUD.showSuccess("Correct!")
        }
        else{
            //Used from -> https://github.com/relatedcode/ProgressHUD
            ProgressHUD.showError("Wrong!")
        }
    
    }
    //when start over, the question number would be zero
    func startOver()
    {
       questionNumber=0
       nextQuestion()
    }
    

    
}
