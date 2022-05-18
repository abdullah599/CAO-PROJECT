package com.example.rfidlockmonitoring

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class dataAdapter(var Data: ArrayList<Data>, var context: Context) :
	RecyclerView.Adapter<RecyclerView.ViewHolder>() {
	val AG = 1
	val AD = 2


	override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
		if(viewType==AG){
			var view=LayoutInflater.from(context).inflate(R.layout.access_granted,parent,false)
			return AgViewholder(view)
		}
		else{
			var view=LayoutInflater.from(context).inflate(R.layout.access_denied,parent,false)
			return Adviewholder(view)
		}
	}

	override fun getItemViewType(position: Int): Int {
		return if (Data[position].status == "Access Granted") AG
		else AD
	}

	override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
		if (Data[position].status== "Access Granted") {
			holder.itemView.findViewById<TextView>(R.id.name_uidAG).text=Data[position].name
			holder.itemView.findViewById<TextView>(R.id.designationAG).text=Data[position].designation
			holder.itemView.findViewById<TextView>(R.id.timeAG).text=Data[position].time
		}
		else{
			holder.itemView.findViewById<TextView>(R.id.name_uidAd).text=Data[position].name
			holder.itemView.findViewById<TextView>(R.id.designationAd).text=Data[position].designation
			holder.itemView.findViewById<TextView>(R.id.timeAd).text=Data[position].time
		}

	}

	override fun getItemCount(): Int {
		return Data.size
	}

	inner class AgViewholder(itemView: View) : RecyclerView.ViewHolder(itemView) {

	}

	inner class Adviewholder(itemView: View) : RecyclerView.ViewHolder(itemView) {

	}
}