using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using System.Collections;

public class Accelerate : MonoBehaviour, IPointerDownHandler, IPointerUpHandler {

	public CarControlScript car;
	private Gear_shift gear;

	void Start(){
		gear = GameObject.Find("Gear").GetComponent<Gear_shift>();
	}

	public void OnPointerDown(PointerEventData eventData){
		if (gear.d_engaged) {
			car.drive ();
		} else {
			car.reverse ();
		}
	}

	public void OnPointerUp(PointerEventData eventData){
		if (gear.d_engaged) {
			car.noDrive ();
		} else {
			car.noReverse ();
		}
	}
}