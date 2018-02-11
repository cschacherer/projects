using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour {

	//Where you want the object to go?
	public float xDistance; 
	public float yDistance; 
	public float zDistance;

	//How fast you want the object to move
	public float speed; 

	//Where the object starts
	private Vector3 startPos; 
	private Vector3 changePos; 

	//Gets starting position
	void Start()
	{
		startPos = new Vector3 (transform.position.x, transform.position.y, transform.position.z); 
	}

	// Moves object
	void Update () {
		changePos = startPos; 

		changePos.x += xDistance * Mathf.Sin(Time.time * speed); 
		changePos.y += yDistance * Mathf.Sin(Time.time * speed); 
		changePos.z += zDistance * Mathf.Sin(Time.time * speed); 

		transform.position = changePos; 
	}
}
