using UnityEngine;
using System.Collections;

public class ProximityMine : MonoBehaviour
{
    //game object for explosion effect
    public GameObject explosion;

    //time in seconds to wait for the explosion
    public float waitTime;
    //the radius of the sphere collider for the mine, which is also the explosion radius that will kill the player
    public float proximityRadius; 
    //how fast you want it to go
    public float movementSpeed;
    //how strong do you want the explosion 
    public float explosionForce; 
    //how far do you want the explosion force to be felt
    public float forceRadius; 

    private bool followPlayer;
    private float globalProximityRadius;

    SphereCollider proximityCollider;
    private bool exploding; 

    private void Start()
    {
        //change sphere collider to desired radius
        proximityCollider = gameObject.GetComponent<SphereCollider>();
        proximityCollider.radius = proximityRadius;
        //get it's global coordinates for Physics.OverlapSphere in Explode function
        globalProximityRadius = proximityCollider.transform.lossyScale.x * proximityCollider.radius;
        followPlayer = false;
        exploding = false;

        //sets tag for game object for Explode function
        gameObject.tag = "Mine"; 
    }

    private void Update()
    {
        if(followPlayer == true)
        {
            //follow the player as it moves
            Transform playerPos = GameObject.FindGameObjectWithTag("Player").transform;
            transform.LookAt(playerPos.position);
            transform.position = Vector3.MoveTowards(transform.position, playerPos.position, movementSpeed * Time.deltaTime);
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        //if player gets into proximity radius, start following it and start timer for explosion
        if (other.tag == "Player" && proximityCollider.enabled) 
        {
            followPlayer = true;
            proximityCollider.enabled = false; 
            StartCoroutine(Wait());
        }
        //if anything runs into the mesh collider, explode 
        else if(!proximityCollider.enabled)
        {
            Explode(); 
        }
    }

    private IEnumerator Wait()
    {
        yield return new WaitForSeconds(waitTime);
        Explode(); 
    }

    private void Explode()
    {
        //start explosion
        exploding = true;
        Instantiate(explosion, transform.position, transform.rotation);
        Destroy(this.gameObject);

       
        //gets all of the collider's within the exoplosion's range
        Collider[] hitColliders = Physics.OverlapSphere(transform.position, globalProximityRadius);
        for (int i = 0; i < hitColliders.Length; i++)
        {
            //kill player if in range
            if (hitColliders[i].tag == "Player")
            {
                Vector3 collisionPosition = hitColliders[i].transform.position;
                Quaternion collisionRotation = Quaternion.LookRotation(hitColliders[i].transform.up);

                /*
                if (!PlayerInformation.instance.dead)
                {
                    PlayerInformation.instance.PlayerDeath(collisionPosition, collisionRotation);
                }*/
            }

            //sets off chain reaction of mine explosions if they are within the blast radius 
            if (hitColliders[i].tag == "Mine" && (hitColliders[i].gameObject.name != this.gameObject.name))
            {
                ProximityMine pm = hitColliders[i].gameObject.GetComponent<ProximityMine>();
                if (pm.exploding == false)
                {
                    pm.Explode();
                }

            }
        }


        //gets all of the collider's within the force distance range to add explosion force to them
        float globalForceRadius = proximityCollider.transform.lossyScale.x * (forceRadius);
        Collider[] forceColliders = Physics.OverlapSphere(transform.position, globalForceRadius);
        for (int i = 0; i < forceColliders.Length; i++)
        {
            //gets parent rigid body
            Rigidbody rb = forceColliders[i].transform.root.gameObject.GetComponent<Rigidbody>();
            if (rb != null && (forceColliders[i].gameObject.name != this.gameObject.name))
            {
                rb.AddExplosionForce(explosionForce, transform.position, globalForceRadius, 1f, ForceMode.Impulse);
            }
            
        }


    }
}