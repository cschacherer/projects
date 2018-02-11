using UnityEngine;
using UnityEditor;

[InitializeOnLoad]
public class StartUpEditor : Editor
{
	static StartUpEditor ()
	{

		EditorApplication.update += Update;
	}

	static void Update ()
	{
		// The base objects are the ones to be snapped by other objects
		GameObject[] baseObjects = GameObject.FindGameObjectsWithTag ("BaseObject");
		// The other objects are the ones to snap to the base objects
		GameObject[] otherObjects = GameObject.FindGameObjectsWithTag ("OtherObject");
		// The unsnap objects are the ones to be unsnapped from the base objects
		GameObject[] unsnapObjects = GameObject.FindGameObjectsWithTag ("UnsnapObject");

		// When an end point of the other object intersects an end point of the base object, snap the two objects base on the endpoints
		foreach (GameObject baseObject in baseObjects) {
			if (baseObject.transform.GetComponent<AssignEndpoint> () == null) {
				baseObject.AddComponent<AssignEndpoint> ();
			}

			foreach (GameObject otherObject in otherObjects) {
				if (otherObject.transform.GetComponent<AssignEndpoint> () == null) {
					otherObject.AddComponent<AssignEndpoint> ();
				}

				foreach (Transform endPointOfOtherObject in otherObject.transform) {
					foreach (Transform endPointOfBaseObject in baseObject.transform) {
						if (endPointOfBaseObject.tag == "EndPoint" && endPointOfOtherObject.tag == "EndPoint") {
							if (endPointOfBaseObject.transform.GetComponent<SphereCollider> ().bounds.Intersects (endPointOfOtherObject.transform.GetComponent<SphereCollider> ().bounds)) {
								otherObject.transform.parent = baseObject.transform;

								otherObject.transform.localRotation = Quaternion.Euler (endPointOfBaseObject.transform.localRotation.eulerAngles.x, endPointOfBaseObject.transform.localRotation.eulerAngles.y, endPointOfBaseObject.transform.localRotation.eulerAngles.z);

								// Gets difference between the Other endpoint and the Base endpoint and then moves the Other transform that difference
								Vector3 diffVector = endPointOfOtherObject.transform.position - endPointOfBaseObject.transform.position;
								otherObject.transform.position = otherObject.transform.position - diffVector;
									  
								otherObject.tag = "BaseObject";

								// Unselects object so there is a clear "snap"
								Selection.activeGameObject = null; 
							}
						}
					}
				}
			}
		}
			
		// An unsnapped object's parent is set to null
		foreach (GameObject unsnapObject in unsnapObjects) {
			unsnapObject.transform.parent = null;

			// Check to see if it has a child and then change tag so it does not show base 
			foreach (Transform child in unsnapObject.GetComponentsInChildren<Transform>()) {
				if (child.tag == "BaseObject") {
					child.tag = "OtherObject"; 
				}
			}
		}
	}
}
