using UnityEngine;
using UnityEditor;

[CustomEditor (typeof(AssignEndpoint))]
public class AssignEndpointEditor : Editor
{

	public override void OnInspectorGUI ()
	{
		base.OnInspectorGUI ();

		AssignEndpoint assignEndpoint = (AssignEndpoint)target;

		if (GUILayout.Button ("Assign An Endpoint")) {
			assignEndpoint.AssignTheEndPoint ();
		}
	}
}
