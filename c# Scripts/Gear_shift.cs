using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Gear_shift : MonoBehaviour {

	public Texture reverse;
	public Texture drive;
	public RawImage img;
	public bool d_engaged = true; //true == drive, false == reverse

	// Use this for initialization
	void Start () {
		img.texture = drive;
		Button button = GetComponent<Button> ();
		button.onClick.AddListener (ChangeImage);

	}


	void ChangeImage(){
		if (d_engaged) {
			img.texture = reverse;
			d_engaged = false;
		}
		else {
			img.texture = drive;
			d_engaged = true;
		}
	}
}
