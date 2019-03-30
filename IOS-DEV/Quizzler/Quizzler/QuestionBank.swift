//
//  QuestionBank.swift
//  Quizzler
//
//  Created by ali mirabzadeh on 3/26/19.


import Foundation
//store a few questions with their answers in a list
class QuestionBank
{
    //constructing a array of Question type
    var list = [Question]()
    //constructing 13 questions and append them to the list of Question
    init()
    {
        // Add questions to the list of Question
        list.append(Question(questionText: "Valentine\'s day is banned in Saudi Arabia.", correctAns: true))
        list.append(Question(questionText: "A slug\'s blood is green.", correctAns: true))
        list.append(Question(questionText: "Approximately one quarter of human bones are in the feet.", correctAns: true))
        list.append(Question(questionText: "The total surface area of two human lungs is approximately 70 square metres.", correctAns: true))
        list.append(Question(questionText: "In West Virginia, USA, if you accidentally hit an animal with your car, you are free to take it home to eat.", correctAns: true))
        list.append(Question(questionText: "In London, UK, if you happen to die in the House of Parliament, you are technically entitled to a state funeral, because the building is considered too sacred a place.", correctAns: false))
        list.append(Question(questionText: "It is illegal to pee in the Ocean in Portugal.", correctAns: true))
        list.append(Question(questionText: "You can lead a cow down stairs but not up stairs.", correctAns: false))
        list.append(Question(questionText: "Google was originally called \"Backrub\".", correctAns: true))
        list.append(Question(questionText: "Buzz Aldrin\'s mother\'s maiden name was \"Moon\".", correctAns: true))
        list.append(Question(questionText: "The loudest sound produced by any animal is 188 decibels. That animal is the African Elephant.", correctAns: false))
        list.append(Question(questionText: "No piece of square dry paper can be folded in half more than 7 times.", correctAns: false))
        list.append(Question(questionText: "Chocolate affects a dog\'s heart and nervous system; a few ounces are enough to kill a small dog.", correctAns: true))
    }
}
