using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CounterScript : MonoBehaviour {

    public int count;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update ()
    {
        var renderers = this.gameObject.GetComponents<Renderer>();
        foreach (var renderer in renderers)
            renderer.enabled = count > 0;
    }
}
