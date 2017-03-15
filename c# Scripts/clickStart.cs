using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using UnityEngine.SceneManagement;

public class clickStart : MonoBehaviour {

	public AudioClip start_clip;

	// Use this for initialization
	void Start () {
		Button startButton = GetComponent<Button> ();
		startButton.onClick.AddListener (TaskOnClick);
	}


	void TaskOnClick () {
		AudioSource.PlayClipAtPoint(start_clip, transform.position);
		SceneManager.LoadScene ("Game", LoadSceneMode.Single);
	}
}
