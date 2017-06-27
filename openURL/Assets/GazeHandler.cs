using HoloToolkit.Unity;
using UnityEngine;

public class GazeHandler : Singleton<GazeHandler>
{

    // Use this for initialization
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
    }

    void OnGazeEnter()
    {
        Debug.Log("OnGazeEnter wurde aufgerufen");
    }

    void OnGazeExit()
    {
        Debug.Log("OnGazeExit wurde aufgerufen");
    }
}