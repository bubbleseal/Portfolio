using UnityEngine;
using System.Collections;

public class BulletFire : MonoBehaviour {

	private Rigidbody bullet;
	public AudioClip impact;

	// Use this for initialization
	void Start ()
	{
		this.bullet = this.GetComponent<Rigidbody> ();
		this.bullet.velocity = transform.forward * 30;
	}
		
	void OnCollisionEnter( Collision other )
	{
		AudioSource.PlayClipAtPoint(impact, transform.position,100.0f);
		Destroy (gameObject);
	}
}
