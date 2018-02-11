using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine; 

namespace Assets._Scripts.Hazards
{
    public class Laser : MonoBehaviour
    {
        private LineRenderer line;

        void Start()
        {
            //set up laser line
            line = GetComponent<LineRenderer>();
        }

        void Update()
        {
            line.SetPosition(0, transform.position);
            Ray ray = new Ray(transform.position, transform.up);

            //see if anything hits the ray
            RaycastHit hit; 
            if(Physics.Raycast(ray, out hit))
            {
                if(hit.collider != null)
                {
                    //change where laser ends after hitting an object
                    line.SetPosition(1, hit.point);

                    ////kill player if it hits the laser
                    if (hit.collider.tag == "Player")
                    {
                        Vector3 collisionPosition = hit.collider.transform.position;
                        Quaternion collisionRotation = Quaternion.LookRotation(hit.collider.transform.up);
                        /*
                        if (!PlayerInformation.instance.dead)
                        {
                            PlayerInformation.instance.PlayerDeath(collisionPosition, collisionRotation);
                        }*/
                    }
                }
            }
            else
            {
                line.SetPosition(1, transform.forward * 100);
            }
            
        }
    }
}
