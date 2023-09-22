#include <stdio.h>
#include <nats/nats.h>
#include <time.h>

int main(int argc, char **argv)
{
    natsConnection *conn = NULL;
    natsOptions *opts = NULL;
    natsStatus s = NATS_OK;

    s = natsOptions_Create(&opts);
    if (s == NATS_OK)
    s = natsOptions_SetNoEcho(opts, true);

    // Connecting to NATS Server
    s = natsConnection_ConnectTo(&conn, "localhost:4222");

    if (s == NATS_OK)
    {
    int64_t mp = natsConnection_GetMaxPayload(conn);
    printf("Max payload: %d\n", (int) mp);
    }
   
    if (s == NATS_OK)
    {   
    	// Start time
        clock_t startTime = clock();
        
        for (int i = 0; i < 1000; i++)
        {
            /* code */
        
        // Streams string to connection for people expecting subject(Foo)
        s = natsConnection_PublishString(conn, "foo", "All is Well");

        
        if (s == NATS_OK)
        //Servera kontrol pingi atarak mesaj gittiğinden emin oluyoruz.
            s = natsConnection_FlushTimeout(conn, 1000);
            //End time
             clock_t endTime = clock();
             //Duration calculation
             double elapsedTime = ((double) (endTime - startTime))/ CLOCKS_PER_SEC  ;

             printf("Message sent in %f seconds", elapsedTime);
        }
    }
    else
    {
        printf("Failed to connect to NATS server\n");
    }

    // Everything created must be destroyed
    natsConnection_Destroy(conn);
    natsOptions_Destroy(opts);

    return 0;
}
