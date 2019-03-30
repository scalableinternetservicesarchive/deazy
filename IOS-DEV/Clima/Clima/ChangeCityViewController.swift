//
//  ChangeCityViewController.swift
//  WeatherApp
//
//  Created by Ali Mirabzadeh on 03/27/2018.
//  Copyright (c) 2019 AMZ Development. All rights reserved.
//

import UIKit


//protocol declaration:
protocol ChangeCityDelegate
{
    func userEnteredANewCityName(city: String)
}
class ChangeCityViewController: UIViewController {
    
    //Declare the delegate:
    var delegate: ChangeCityDelegate?
    
    //This is the pre-linked IBOutlets to the text field:
    @IBOutlet weak var changeCityTextField: UITextField!

    
    //This is the IBAction that gets called when the user taps on the "Get Weather" button:
    @IBAction func getWeatherPressed(_ sender: AnyObject) {
        //1 Get the city name the user entered in the text field
        let cityName = changeCityTextField.text!
        //2 If we have a delegate set, call the method userEnteredANewCityName
        // '?' checks if delegate has a value then call the method, otherwise doesn't do anything
        delegate?.userEnteredANewCityName(city: cityName)
        //3 dismiss the Change City View Controller to go back to the WeatherViewController
        self.dismiss(animated: true, completion: nil)
    }
    
    

    //This is the IBAction that gets called when the user taps the back button. It dismisses the ChangeCityViewController.
    @IBAction func backButtonPressed(_ sender: AnyObject) {
        self.dismiss(animated: true, completion: nil)
    }
    
}
