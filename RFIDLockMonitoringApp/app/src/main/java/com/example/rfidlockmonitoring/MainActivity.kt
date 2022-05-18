package com.example.rfidlockmonitoring

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.rfidlockmonitoring.databinding.AccessDeniedBinding
import com.example.rfidlockmonitoring.databinding.ActivityMainBinding
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener

class MainActivity : AppCompatActivity() {
	lateinit var binding: ActivityMainBinding
	lateinit var Data: ArrayList<Data>
	lateinit var adapter: dataAdapter

	override fun onCreate(savedInstanceState: Bundle?) {
		super.onCreate(savedInstanceState)
		binding = ActivityMainBinding.inflate(layoutInflater)
		setTheme(R.style.Theme_RFIDLockMonitoring)
		setContentView(binding.root)
		Data = ArrayList()
		adapter = dataAdapter(Data, this)
		binding.recyclerview.adapter = adapter
		binding.recyclerview.layoutManager = LinearLayoutManager(this)
		getData()


	}

	private fun getData() {
		val database = FirebaseDatabase.getInstance().getReference("data")
		database.addValueEventListener(object : ValueEventListener {
			override fun onDataChange(snapshot: DataSnapshot) {
				if (snapshot.exists()) {
					Data.clear()
					for (Snapshot in snapshot.children) {

						if (Snapshot.child("Name").value.toString() != "null"){
							Data.add(Data(Snapshot.child("Name").value.toString(),
							     Snapshot.child("Designation").value.toString(),
							     Snapshot.child("Time").value.toString(),
							     Snapshot.child("Status").value.toString()))

						}

						else {

							Data.add(Data(Snapshot.child("Uid").value.toString(),
							              "Unknown",
							              Snapshot.child("Time").value.toString(),
							              Snapshot.child("Status").value.toString()))
						}
					}
					adapter.notifyDataSetChanged()


				}
			}

			override fun onCancelled(error: DatabaseError) {
				TODO("Not yet implemented")
			}
		})

	}
}