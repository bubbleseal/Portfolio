using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using UnityEngine.EventSystems;

public class Brake : MonoBehaviour, IPointerUpHandler, IPointerDownHandler {

	public CarControlScript car;

	public void OnPointerDown(PointerEventData eventData){
		car.brake ();
	}

	public void OnPointerUp(PointerEventData eventData){
		car.noBrake ();
	}
}