using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boost : MonoBehaviour {

    public float boost;
    private MeshCollider mc; 

	// Use this for initialization
	void Start () {
        gameObject.AddComponent<MeshCollider>();
        mc = gameObject.GetComponent<MeshCollider>(); 
        mc.convex = true; 
        mc.isTrigger = true; 
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    void OnTriggerEnter(Collider other)
    {
        if (other.tag == "PlayerCollider")
        {
            float newBoost = ShipMovement_Rigidbody.instance.boost + boost; 
            if (newBoost < 100)
            {
                newBoost = 100; 
            }
            ShipMovement_Rigidbody.instance.boost = newBoost;

            Destroy(this.gameObject);  
        }
    }
}
