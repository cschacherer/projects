using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossAI : MonoBehaviour {

    //different speeds for boss
    float movementSpeed;
    float rotationSpeed;
    float shortAttackSpeed;
    float longAttackSpeed;

    float shortRangeAttackDistance; 

    //this is used for when the boss is circling
    float timeCounter;
    //this is used to keep track of how many times the boss can hit the mountain before it dies 
    int damageCount;
    //keeps track if the boss is in the middle of long range attack
    bool preparingAttack; 
    bool attacking;

    bool aquiredLongRangeTarget; 

    //boss's rigid body 
    Rigidbody rb;

    //used to keep track of the player and where the boss wants to go
    Transform player;
    Transform target;
    Vector3 distanceFromPlayer;

    //keeps track of what state the boss is in 
    BossActionType currentState;

    public enum BossActionType
    {
        CircleArea,
        FollowPlayer,
        ShortRangeAttack,
        LongRangeAttack,
        HitBorder,
        TakeDamage,
        Die
    }

    void Start() {
        //sets the initial values 
        movementSpeed = 20;
        rotationSpeed = 5;
        shortAttackSpeed = movementSpeed * 2;
        longAttackSpeed = movementSpeed * 6;

        shortRangeAttackDistance = 7; 

        timeCounter = 0;

        rb = GetComponent<Rigidbody>(); 

        player = GameObject.FindGameObjectWithTag("Player").transform;
        target = player.transform;
        distanceFromPlayer = player.position - transform.position;

        attacking = false;
        preparingAttack = false;

        damageCount = 3; 


        aquiredLongRangeTarget = false;

        currentState = BossActionType.CircleArea;
        RandomAction(); 
        
    }

    void Update()
    {
        //always know where the player is 
        player = GameObject.FindGameObjectWithTag("Player").transform;
        distanceFromPlayer = player.position - transform.position;

        Debug.Log("boss type: " + currentState); 

        if(currentState == BossActionType.CircleArea)
        {
            CircleArea(30);
        }
        else if (currentState == BossActionType.FollowPlayer)
        {
            FollowPlayer();
        }
        else if (currentState == BossActionType.ShortRangeAttack)
        {
            ShortRangeAttack();
        }
        else if (currentState == BossActionType.LongRangeAttack)
        {
            LongRangeAttack();
        }
        else if (currentState == BossActionType.HitBorder)
        {
            HitBorder(); 
        }
        else if (currentState == BossActionType.TakeDamage)
        {
            TakeDamage(); 
        }
        else if (currentState == BossActionType.Die)
        {
            Die(); 
        }

    }  

    void RandomAction()
    {
        System.Random rand = new System.Random();
        int seconds = rand.Next(1, 5);
        StartCoroutine(WaitForAction(seconds)); 
    }

    private IEnumerator WaitForAction(int seconds)
    {
        yield return new WaitForSeconds(seconds);
        if (currentState == BossActionType.CircleArea || currentState == BossActionType.FollowPlayer)
        {
            System.Random waitRandom = new System.Random();
            int action = waitRandom.Next(1, 3);
            Debug.Log("rand action: " + action); 
            //circle area
            if(action == 1)
            {
                currentState = BossActionType.CircleArea; 
            }
            //follow player
            else if (action == 2)
            {
                currentState = BossActionType.FollowPlayer; 
            }
            //long range attack
            else if (action == 3)
            {
                currentState = BossActionType.LongRangeAttack;
            }  
        }
        RandomAction();
    }

    void CircleArea(float width)
    {
        float circleSpeed = 1;
        float xWidth = width;
        float zWidth = width;

        timeCounter += Time.deltaTime * circleSpeed;

        transform.LookAt(new Vector3(Mathf.Cos(timeCounter) * xWidth, 0, Mathf.Sin(timeCounter) * zWidth));
        transform.position = new Vector3(Mathf.Cos(timeCounter) * xWidth, 0, Mathf.Sin(timeCounter) * zWidth);

        CheckShortRangeDistance(); 
    }

    void FollowPlayer()
    {
        transform.LookAt(player.position);
        transform.position = Vector3.MoveTowards(transform.position, player.position, movementSpeed * Time.deltaTime);

        CheckShortRangeDistance(); 
    }

    void CheckShortRangeDistance()
    {
        if (distanceFromPlayer.magnitude < 10)
        {
            target.position = player.position;
            currentState = BossActionType.ShortRangeAttack;
        }
    }

    void ShortRangeAttack()
    {
        //look towards the target and move towards it 
        float attackSpeed = movementSpeed * 10;
        Quaternion newRotation = Quaternion.LookRotation(target.position - transform.position);
        transform.rotation = Quaternion.Slerp(transform.rotation, newRotation, rotationSpeed * Time.deltaTime);
        transform.position = Vector3.MoveTowards(transform.position, target.position, shortAttackSpeed * Time.deltaTime);

        //if it reaches the position where the player was, have it circle around 
        if(transform.position == target.position)
        {
            currentState = BossActionType.CircleArea; 
        }
    }

    //Boss does a long range attack on the player 
    void LongRangeAttack()
    {
       // LineRenderer line = GetComponent<LineRenderer>(); 
        
        if (aquiredLongRangeTarget == false)
        {
            CircleArea(40);
            //line.SetPosition(0, transform.position);

            Ray ray = new Ray(transform.position, player.position - transform.position);

            //see if anything hits the ray
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
            {
                if (hit.collider != null)
                {
                    Debug.Log("collider");
                    //line.SetPosition(1, hit.point);
                    ////kill player if it hits the laser
                    if (hit.collider.gameObject.tag == "Mountain")
                    {
                        Debug.Log("hit mountain");
                    }
                    if (hit.collider.gameObject.tag == "Player")
                    {
                        Debug.Log("hit player");
                        target.position = player.position;
                        transform.LookAt(target.position); 
                        aquiredLongRangeTarget = true; 
                    }
                }
            }
        }
        else
        {
            Debug.Log("moving"); 
            transform.Translate(transform.forward * Time.deltaTime * longAttackSpeed, Space.World);
            if(transform.position == target.position)
            {
                currentState = BossActionType.CircleArea;
                aquiredLongRangeTarget = false; 
            }
        }
    }

    //Boss hits border and turns around
    void HitBorder()
    {
        Vector3 relativePos = Vector3.zero - transform.position;
        Quaternion rotation = Quaternion.LookRotation(relativePos);
        transform.rotation = Quaternion.Slerp(transform.rotation, rotation, rotationSpeed * Time.deltaTime);
        currentState = BossActionType.FollowPlayer;
    }

    //Boss has hit the mountain 
    void TakeDamage()
    {
        damageCount--;
        if (damageCount == 0)
        {
            currentState = BossActionType.Die; 
        }
        else
        {
            currentState = BossActionType.CircleArea; 
        }
    }

    //Boss has been defeated
    void Die()
    {
        Destroy(this); 
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            Debug.Log("hit player trigger");
            currentState = BossActionType.CircleArea; 
            //target.position = player.position;
            //if(aquiredLongRangeTarget == true)
            //{
            //    currentState = BossActionType.ShortRangeAttack;
            //}
            
        }
        if(other.tag == "Mountain")
        {
            Debug.Log("hit mountain trigger"); 
            currentState = BossActionType.TakeDamage; 
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.tag == "SphereContainer")
        {
            Debug.Log("hit border");

            currentState = BossActionType.HitBorder;

            if(aquiredLongRangeTarget == true)
            {
                aquiredLongRangeTarget = false; 
            }
        }
    }
}
