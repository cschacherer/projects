using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AssignEndpoint : MonoBehaviour
{
	public float radius = 1;
	public GameObject endPoint;

	void Start ()
	{
		AssignTheEndPoint ();
	}

	public void AssignTheEndPoint ()
	{
		endPoint = GameObject.CreatePrimitive (PrimitiveType.Sphere);
		endPoint.transform.localScale = new Vector3 ((float)(gameObject.transform.localScale.x / 10), (float)(gameObject.transform.localScale.y / 10), (float)(gameObject.transform.localScale.z / 10));
		endPoint.transform.localPosition = new Vector3 (gameObject.transform.localPosition.x + gameObject.transform.localScale.x, gameObject.transform.localPosition.y, gameObject.transform.localPosition.z);
		endPoint.transform.parent = gameObject.transform;
		endPoint.tag = "EndPoint";
		endPoint.name = "SphereEndpoint"; 
		endPoint.GetComponent<SphereCollider> ().radius = radius;
	}
}
