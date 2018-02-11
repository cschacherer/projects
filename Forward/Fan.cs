using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Fan : MonoBehaviour {

    public int force;

    private float colliderDistance;
    private BoxCollider boxCollider;

	// Use this for initialization
	void Start () {
        boxCollider = gameObject.GetComponent<BoxCollider>();
        //calculate how big the box collider is, so where you want the wind to blow
        colliderDistance = transform.lossyScale.z * boxCollider.size.z; 
    }
	
	// Update is called once per frame
	void Update () {
		
	}

    void OnTriggerStay(Collider collider)
    { 
        if (collider.tag == "PlayerCollider")
        {
            //get how far away the player is from the fan and make the force applied 
            //proportional to the distance.  
            GameObject player = collider.transform.root.gameObject;
            Vector3 distance = gameObject.transform.position - player.transform.position;
            float magnitude = 1 - Mathf.Abs(distance.magnitude / colliderDistance);
            float totalForce = force * magnitude;

            Rigidbody rb = player.GetComponent<Rigidbody>();
            rb.AddForce(transform.forward * totalForce);
        }
    }
}
