using UnityEngine;
using System.Collections;

public class Float : MonoBehaviour {

	public float amplitude;


	// Update is called once per frame
	void Update () {
		transform.position = new Vector3 (transform.position.x , transform.position.y + amplitude * Mathf.Sin(2 * Time.time) , transform.position.z); //Bounce animation
		transform.Rotate (0.0f, 60 * Time.deltaTime, 0.0f, Space.World); //Rotation
	}
}
