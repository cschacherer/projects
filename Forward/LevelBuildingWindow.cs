using UnityEngine;
using UnityEditor;

public class LevelBuildingWindow : EditorWindow
{
	[MenuItem ("Window/LevelBuilding")]
	public static void ShowWindow ()
	{
		GetWindow<LevelBuildingWindow> ("Build Your Level");
	}

	void OnGUI ()
	{
		if (GUILayout.Button ("Make Endpoints Visible")) {
			GameObject[] endPoints = GameObject.FindGameObjectsWithTag ("EndPoint");
			foreach (GameObject endPoint in endPoints) {
				endPoint.GetComponent<MeshRenderer> ().enabled = true; 
			}
		}

		if (GUILayout.Button ("Make Endpoints Invisible")) {
			GameObject[] endPoints = GameObject.FindGameObjectsWithTag ("EndPoint");
			foreach (GameObject endPoint in endPoints) {
				endPoint.GetComponent<MeshRenderer> ().enabled = false; 
			}
		}
	}
}
