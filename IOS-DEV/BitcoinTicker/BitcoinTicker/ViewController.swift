//
//  ViewController.swift
//  BitcoinTicker
//
//  Created by Angela Yu on 23/01/2016.
//  Copyright © 2016 London App Brewery. All rights reserved.
//

import UIKit
import Alamofire // for http request
import SwiftyJSON //for JSON parsing

class ViewController: UIViewController, UIPickerViewDelegate, UIPickerViewDataSource {
    //API URL
    let baseURL = "https://apiv2.bitcoinaverage.com/indices/global/ticker/BTC"
    //different currencies' name that will be appeared on currenyPicker
    let currencyArray = ["AUD", "BRL","CAD","CNY","EUR","GBP","HKD","IDR","ILS","INR","JPY","MXN","NOK","NZD","PLN","RON","RUB","SEK","SGD","USD","ZAR"]
    //different currencies' sign
    let currencySignArray = ["$", "R$", "$", "¥", "€", "£", "$", "Rp", "₪", "₹", "¥", "$", "kr", "$", "zł", "lei", "₽", "kr", "$", "$", "R"]
    var finalURL = ""
    var selectedCurrencySign: Int?
    //IBOutlets
    @IBOutlet weak var bitcoinPriceLabel: UILabel!
    @IBOutlet weak var currencyPicker: UIPickerView!
    //when first load the app
    override func viewDidLoad() {
        super.viewDidLoad()
        currencyPicker.delegate = self
        currencyPicker.dataSource = self
    }
    //determine how many columns we want in our picker
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        //only returns one column
        return 1
    }
    //rows this picker should have using the pickerView(numberOfRowsInComponent:) method.
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return currencyArray.count
    }
    //fill the picker row titles with the Strings from our currencyArray using the pickerView:titleForRow: method
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return currencyArray[row]
    }
    //This will get called every time the picker is scrolled. When that happens it will record the row that was selected.
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        //based on the the currency selected, concantinate the desired currency to the base one and store in the finla version
        finalURL = baseURL + currencyArray[row]
        selectedCurrencySign = row
        getBitcoinData(url: finalURL)
    }
//    //MARK: - Networking
//    /***************************************************************/
    func getBitcoinData(url: String)
    {
        //using Alamofire library  to do a get request
        Alamofire.request(url, method: .get).responseJSON
        {
            //store the date from the call in response
            response in
            if response.result.isSuccess
            {
                //parse the value from the json file to pass into the JSON parser function
                let bitCoinCurrency : JSON = JSON(response.result.value!)
                //call the JSON parser function
                self.updateBitcoinData(json: bitCoinCurrency)
            }
            else
            {
                //if couldn't get the data, output the following instead of showing the price
                self.bitcoinPriceLabel.text = "Connection Issues"
            }
        }

    }
//    //MARK: - JSON Parsing
//    /***************************************************************/
    func updateBitcoinData(json : JSON)
    {
        //if was able to parse the data
        if let bitCoinPrice = json["ask"].double
        {
            //show the price of the selected currency with its sign
            bitcoinPriceLabel.text = currencySignArray[selectedCurrencySign!] + " " + String(bitCoinPrice)
        }
        else
        {
            //if couldn't get the price show the following message
            bitcoinPriceLabel.text = "Currency Unavailable!"
        }
       
    }
}

