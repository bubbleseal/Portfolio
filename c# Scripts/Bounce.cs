using UnityEngine;
using System.Collections;

public class Bounce : MonoBehaviour {

	public float amplitude;

	// Update is called once per frame
	void Update () {
		transform.position = new Vector3 (transform.position.x , transform.position.y + amplitude * Mathf.Sin(2 * Time.time) , transform.position.z); //Bounce animation
	}

	void OnTriggerEnter(Collider other){

		if (other.gameObject.CompareTag ("Player")) {
			Destroy (gameObject);
		}
	}
}
