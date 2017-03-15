using UnityEngine;
using System.Collections;

public class Bullet_Impact : MonoBehaviour {

	public AudioClip Explosion;
	public GameObject Explode_fx;

	void OnTriggerEnter(Collider other){
	
		if (other.gameObject.CompareTag ("Boulder")) { 
			AudioSource.PlayClipAtPoint (Explosion, transform.position); //Play Explosion audio clip
			Instantiate (Explode_fx, transform.position, transform.rotation); //Run explosion vfx
			Destroy (other.gameObject); //Destroy boulder obstacle
		}
	}

}
