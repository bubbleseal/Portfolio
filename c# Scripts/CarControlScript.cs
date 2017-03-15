using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class CarControlScript : MonoBehaviour {
	public WheelCollider WheelFL;
	public WheelCollider WheelFR;
	public WheelCollider WheelRL;
	public WheelCollider WheelRR;

	public Transform WheelFLTrans;
	public Transform WheelFRTrans;
	public Transform WheelRLTrans;
	public Transform WheelRRTrans;

	public GameObject truckBody;
	public Material normalMat;
	public Material brakeMat;
	public Material reverseMat;
	bool braked = false;
	float maxBrakeTorque = 150;

	private float maxTorque = 100;

	float lowestSteerAtSpeed = 50;
	float lowSpeedSteerAngle = 10;
	float highSpeedSteerAngle = 1;
	float decelerationSpeed = 40;
	public float currentSpeed;

	public float carSpeed = 0f;
	float topSpeed = 125;

	///////////////////////////////

	public bool mobileInput;
	public float steeringForce = 7;
	public bool driving;
	public bool reversing;

	///////////////////////////////

	private float mySidewayFriction;
	private float myForwardFriction;
	private float slipSidewayFriction;
	private float slipForwardFriction;
	private int[] gearRatio;

	///////////////////////////////

	public Text onScreenText;
	public Button fire;


	public GameObject shot;
	public Transform spawnPoint;
	public float fireRate;
	private float nextFire;

	public AudioClip launcher_clip;

	// Use this for initialization

	void Start () {

		GetComponent<Rigidbody> ().centerOfMass = new Vector3 (0, 0, 0);
		setValues ();

		///////////////////

		// change this flag to true if your deploying to a mobile device

		//mobileInput = false ;

		// these flags register the state of the vehicle - driving, reversing;
		driving = false;
		reversing = false;

		///////////////////

		// set text & fire button to false
		onScreenText.enabled = false;
		fire.gameObject.SetActive(false);

	}

	void setValues()
	{
		myForwardFriction = WheelRR.forwardFriction.stiffness;
		mySidewayFriction = WheelRR.sidewaysFriction.stiffness;
		slipForwardFriction = 0.01f;
		slipSidewayFriction = 0.005f;
		gearRatio = new int[5];
		gearRatio[0] = 20;  gearRatio[1] = 50; gearRatio[2] = 80;
		gearRatio[3] = 110; gearRatio[4] = (int)(topSpeed+5); //>topspeed
	}

	void FixedUpdate () {
		Control ();
		HandBrake();
	}

	void Control()
	{
		currentSpeed = (2*3.1415926f *WheelRL.radius*WheelRL.rpm*60/1000)/0.4f;
		//currentSpeed = GetComponent<Rigidbody>().velocity.magnitude*3.6f/0.4f;
		currentSpeed = Mathf.Round(currentSpeed);
		if(currentSpeed < topSpeed)
		{

			if(mobileInput){

			  WheelRR.motorTorque = maxTorque * carSpeed;
			  WheelRL.motorTorque = maxTorque * carSpeed;
			}

		    else {

			  WheelRR.motorTorque = maxTorque * Input.GetAxis("Vertical");
			  WheelRL.motorTorque = maxTorque * Input.GetAxis("Vertical");

				}
		}

		else
		{
			WheelRR.motorTorque = 0;
			WheelRL.motorTorque = 0;
		}
		
		float speedFactor = currentSpeed/lowestSteerAtSpeed;
		float currentSteerAngle = Mathf.Lerp(lowSpeedSteerAngle,highSpeedSteerAngle,speedFactor);

		  
		// Code to control the car via the accelerometer

		///////////////////////////////////////////////////////////

		if (mobileInput) { // if the mobile flag is set in the start method run this branch
			currentSteerAngle *= Input.acceleration.x * steeringForce;		
		} else { // otherwise use the keyboard keys
			currentSteerAngle *= Input.GetAxis ("Horizontal"); 
		}

		///////////////////////////////////////////////////////////

		WheelFL.steerAngle = currentSteerAngle;
		WheelFR.steerAngle = currentSteerAngle;

/*
		if(Input.GetButton("Vertical")==false) //if no gas, slow down the car
		{
			WheelRR.brakeTorque = decelerationSpeed;
			WheelRL.brakeTorque = decelerationSpeed;
		}
		else
	    {
			WheelRR.brakeTorque = 0;
			WheelRL.brakeTorque = 0;
	}

*/	
	}

	// Update is called once per frame
	void Update()
	{
		haltCar (); // halt the car on based on the state of the boolean flags

		WheelFLTrans.Rotate(WheelFL.rpm/60*360*Time.deltaTime,0,0);
		WheelFRTrans.Rotate(WheelFR.rpm/60*360*Time.deltaTime,0,0);
		WheelRLTrans.Rotate(WheelRL.rpm/60*360*Time.deltaTime,0,0);
		WheelRRTrans.Rotate(WheelRR.rpm/60*360*Time.deltaTime,0,0);

		float ttFL = WheelFL.steerAngle - WheelFLTrans.localEulerAngles.z;
		float ttFR = WheelFR.steerAngle - WheelFRTrans.localEulerAngles.z;
		Vector3 AngleFL = new Vector3 (WheelFLTrans.localEulerAngles.x,ttFL,WheelFLTrans.localEulerAngles.z);
		WheelFLTrans.localEulerAngles = AngleFL;
		Vector3 AngleFR = new Vector3 (WheelFRTrans.localEulerAngles.x,ttFR,WheelFRTrans.localEulerAngles.z);
		WheelFRTrans.localEulerAngles = AngleFR;

		BrakeLight(); 
		EngineSound();

		fire.onClick.AddListener (fireBullet);
	}

	void BrakeLight()
	{
		if(currentSpeed > 0 && Input.GetAxis ("Vertical") < 0 )
			truckBody.GetComponent<Renderer>().material = brakeMat;
		else if(currentSpeed < 0 && Input.GetAxis ("Vertical") > 0 )
			truckBody.GetComponent<Renderer>().material = brakeMat;
		else if(currentSpeed < 0 && Input.GetAxis ("Vertical") < 0 )
			truckBody.GetComponent<Renderer>().material = reverseMat;
		else
			truckBody.GetComponent<Renderer>().material = normalMat;
	}

	void EngineSound()
	{
		/*int i;
		for(i=0;i<gearRatio.Length;i++)
		{
			if(gearRatio[i] > currentSpeed ) break;
		}
		float gearMinValue =0;
		float gearMaxValue =0;
		if(i==0)
		{
			gearMinValue =0; gearMaxValue = gearRatio[i];
		}
		else
		{
			gearMinValue = gearRatio[i-1]; 
			gearMaxValue = gearRatio[i];
		}
		float enginePitch = ((currentSpeed - gearMinValue)/(gearMaxValue-gearMinValue))+1;
		GetComponent<AudioSource>().pitch  = enginePitch;*/
		GetComponent<AudioSource>().pitch = currentSpeed/topSpeed+1;
	}

	void HandBrake()
	{
		/*if(Input.GetButton("Jump"))
		{
			braked = true;
		}
		else
		{
			braked = false;
		}*/
		if(braked)
		{
			WheelFR.brakeTorque = maxBrakeTorque;
			WheelFL.brakeTorque = maxBrakeTorque;
			WheelRR.motorTorque = 0;
			WheelRL.motorTorque = 0;
			if(GetComponent<Rigidbody>().velocity.magnitude>1)
				SetSlip(slipForwardFriction, slipSidewayFriction);
			else
				SetSlip (1, 1);
			if(currentSpeed <1 && currentSpeed >-1)
				truckBody.GetComponent<Renderer>().material = normalMat;
			else
				truckBody.GetComponent<Renderer>().material = brakeMat;
		}
		else
		{
			SetSlip(myForwardFriction,mySidewayFriction);
			WheelFR.brakeTorque = 0;
			WheelFL.brakeTorque = 0;
		}
	}
	
	void SetSlip(float currentForwardFriction, float currentSidewayFriction)
	{
		WheelFrictionCurve rr = WheelRR.forwardFriction;
		WheelFrictionCurve rl = WheelRL.forwardFriction;
		rr.stiffness = currentForwardFriction;
		rl.stiffness = currentForwardFriction;
		WheelRR.forwardFriction = rr;
		WheelRL.forwardFriction = rl;
		
		rr = WheelRR.sidewaysFriction;
		rl = WheelRL.sidewaysFriction;
		rr.stiffness = currentSidewayFriction;
		rl.stiffness = currentSidewayFriction;
		WheelRR.sidewaysFriction = rr;
		WheelRL.sidewaysFriction = rl;
	}
		
	void haltCar(){
		if(!driving && ! reversing){
			carSpeed = 0;
		}
	}

	public void drive (){
		carSpeed ++;
		driving = true;
	}

	public void noDrive (){
		driving = false;
	}


	public void reverse (){
		truckBody.GetComponent<Renderer>().material = reverseMat;
		carSpeed --;

		reversing = true;

	}

	public void noReverse (){

		reversing = false;
		truckBody.GetComponent<Renderer>().material = normalMat;
	}


	public void brake (){
		truckBody.GetComponent<Renderer>().material = reverseMat;
		braked = true;

	}

	public void noBrake (){
		braked = false;
		truckBody.GetComponent<Renderer>().material = normalMat;
	}
		

	void OnTriggerEnter(Collider other){
		if (other.gameObject.CompareTag ("Water")) { //Display Game over when player falls into water
			SceneManager.LoadScene ("GameOver", LoadSceneMode.Single);

		} else if (other.gameObject.CompareTag ("End")) {
			SceneManager.LoadScene ("YouWin", LoadSceneMode.Single);
		}
		else if (other.gameObject.CompareTag ("Rocket_Launcher")) { //Rocket launcher captured
			StartCoroutine (updateText ("Rocket Launcher obtained", 3)); 
			AudioSource.PlayClipAtPoint(launcher_clip, transform.position);
			Destroy (other.gameObject); //Destroy rocket launcher
			Destroy (GameObject.FindWithTag("Marker_1")); //Destroy markers
			Destroy (GameObject.FindWithTag("Marker_2")); //Destroy markers
			fire.gameObject.SetActive(true);
		}

	}


	//UI text for On Screen text
	IEnumerator updateText(string text, float delay)
	{
		onScreenText.text = text ;
		onScreenText.enabled = true;
		yield return new WaitForSeconds(delay);
		onScreenText.enabled = false;
	}

	void fireBullet(){
		if (Time.time > nextFire) {
			nextFire = Time.time + fireRate;
			Rigidbody newBullet = Instantiate(shot,spawnPoint.position,spawnPoint.rotation)as Rigidbody;
		}
	}

}
