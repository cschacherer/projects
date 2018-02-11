using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Security.Cryptography; 

public class RandomRotator : MonoBehaviour
{
    
    private float x;
    private float y;
    private float z;

    private int speed;

    //initialize variables
    private void Start()
    {
        x = UnityEngine.Random.Range(-180, 180);
        y = UnityEngine.Random.Range(-180, 180);
        z = UnityEngine.Random.Range(-180, 180);

        //makes sure the speed is not zero
        speed = UnityEngine.Random.Range(-5, 5);
        while (speed == 0)
        {
            speed = UnityEngine.Random.Range(-5, 5);
        }
    }

    // Will rotate object to chosen speed
    void Update()
    {
        transform.Rotate(new Vector3(x, y, z) * Time.deltaTime * speed); 
    }
}
