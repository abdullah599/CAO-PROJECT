package com.example.rfidlockmonitoring

class Data
{
	var name="Unknown"
	var designation="Unknown"
	var time="Unknown"
	var status="Unknown"

	constructor(){}
	constructor( n:String, des:String,t:String,s:String){
		name=n
		designation=des
		time=t
		status=s
	}
}