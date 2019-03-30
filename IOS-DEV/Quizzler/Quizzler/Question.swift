//
//  Question.swift
//  Quizzler
//
//  Created by ali mirabzadeh on 3/26/19.


import Foundation


class Question
{
    let question: String
    let answer : Bool
    
    //initiallizing
    init(questionText: String, correctAns : Bool)
    {
        question = questionText
        answer = correctAns
    }
}
