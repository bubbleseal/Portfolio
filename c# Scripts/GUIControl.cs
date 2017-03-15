using UnityEngine;
using System.Collections;


// add this script to an empty game object called Control



public class GUIControl : MonoBehaviour {
	

	// create GameObject variable
	GameObject carControl;

	// Use this for initialization
	void Start () {
		
		// assign the GameObject called Car to the GameObject variable
		// this must exactly match the GameObject name in the Hierarchy
		carControl = GameObject.Find("Car"); 
	}
		
	public void OnGUI () {

		// create some GUI buttons		
		if (GUI.Button (new Rect (400,600,300,100), "Accelerate")) {
			
			// get the component (script) attached to the Car GameObject and
			// call its drive() method
			carControl.GetComponent<CarControlScript>().drive();

		}

		if (GUI.Button (new Rect (10,600,300,100), "Brake")) {

			// put your code here
			
		}

		if (GUI.Button (new Rect (800, 600, 300, 100), "Reverse")) {

			// put your code here
		
			
		}



	}

	
	// Update is called once per frame

	void Update () {
		

		
	}
	

}
