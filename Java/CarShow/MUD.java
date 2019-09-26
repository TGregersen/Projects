package car.show;

import java.util.Arrays;

import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoCursor;
import com.mongodb.client.MongoDatabase;
import static com.mongodb.client.model.Filters.eq;
import org.bson.Document;
import com.mongodb.*;

public class MUD{

    private final static String HOST = "localhost";
    private final static int PORT = 27017;
    private final static String DATABASE = "show";
    private final static String USER = "mano";
    private final static String PASSWORD = "pw23";

    private MongoCredential mCredential;
    private MongoClient mClient;
    private MongoDatabase mDatabase;
    private MongoCollection<Document> collection;

    public MUD() {
        mCredential = MongoCredential.createCredential(USER, DATABASE, PASSWORD.toCharArray());
        mClient = new MongoClient(new ServerAddress(HOST, PORT), Arrays.asList(mCredential));
        mDatabase = mClient.getDatabase(DATABASE);
        collection = mDatabase.getCollection("Drivers");
    }

    public void create(String idCode, String name, String year, String make, String model, String category){
        try{
            mClient.getDatabase(DATABASE)
                    .getCollection("Drivers").insertOne(new Document()
                    .append("idCode", idCode)
                    .append("Name", name)
                    .append("Year", year)
                    .append("Make", make)
                    .append("Model", model)
                    .append("Category", category)
                    .append("Votes", 0));
        }catch(Exception e){
            System.out.println(e.getMessage());
        }
    }

    public void overWrite(String idCode, String name, String year, String make, String model, String category){
        try{
            FindIterable<Document> doc = collection.find(eq("idCode", idCode));
            MongoCursor<Document> cursor = doc.iterator();
            int value = 0;

            while(cursor.hasNext()){
                Document r = cursor.next();
                value = ((Number)r.get("Votes")).intValue();
            }

            collection.updateOne(eq("idCode", idCode),
                    new Document("$set", new Document("Name", name)
                            .append("Year", year)
                            .append("Make", make)
                            .append("Model", model)
                            .append("Category", category)
                            .append("Votes", value)));

        }catch(Exception e){
            System.out.println(e.getMessage());
        }

    }

    public void readAll() {
        try{
            FindIterable<Document> iter = mClient
                    .getDatabase(DATABASE)
                    .getCollection("Drivers").find();

            iter.forEach(new Block<Document>(){
                @Override
                public void apply(Document doc){
                    System.out.println(doc);
                }
            });

        }catch(Exception e){
            System.out.println(e.getMessage());
        }
    }

    public Document read(String idCode){
        Document r = new Document();

        try{
            FindIterable<Document> doc = collection.find(eq("idCode", idCode));
            MongoCursor<Document> cursor = doc.iterator();

            while(cursor.hasNext()){
                r = cursor.next();
            }
        }catch(Exception e){
            System.out.println(e.getMessage());
        }

        return r;
    }

    public void increaseVote(String idCode) {
        try{
            FindIterable<Document> doc = collection.find(eq("idCode", idCode));
            MongoCursor<Document> cursor = doc.iterator();
            int value = 0;

            while(cursor.hasNext()){
                Document r = cursor.next();
                value = ((Number)r.get("Votes")).intValue();
            }

            value++;

            Document newDoc = new Document();
            newDoc.append("$set", new Document("Votes", value));

            mClient.getDatabase(DATABASE).getCollection("Drivers").updateOne(eq("idCode", idCode), newDoc);

        }catch(Exception e){
            System.out.println(e.getMessage());
        }
    }

    public void printWin (String category){
        FindIterable<Document> doc = collection.find(eq("Category", category))
                .sort(new BasicDBObject("Votes",-1));
        MongoCursor<Document> cursor = doc.iterator();
        int count = 0;
        while(count < 3){
            Document r = cursor.next();
            System.out.println(r); // To a document.
            count++;
        }
    }

    public void deleteOne(String idcode){
        collection.deleteOne(eq("idCode", idcode));
    }

    public void deleteMany(){
        collection.drop();
    }
}