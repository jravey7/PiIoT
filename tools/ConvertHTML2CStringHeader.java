import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.BufferedWriter;
import java.io.FileWriter;

public class ConvertHTML2CStringHeader {
    public static void main(String[] args) throws IOException {

        for(String arg : args)
        {
            if(arg.contains("-h"))
            {
                System.out.println("\nUsage: ConvertHTML2CStringHeader [inputFilePath] [outputFilePath] [c string variable name]\n");
                return;
            }
        }

        String inputFilePath = "page.html";
        if(args.length > 0)
        {
            inputFilePath = args[0];
        }

        String outputFilePath = "htmlPage.h";
        if(args.length > 1)
        {
            outputFilePath = args[1];
        }

        String cStringVarName = "htmlPage";
        if(args.length > 2)
        {
            cStringVarName = args[2];
        }

        String headerSymbol = outputFilePath.substring(0, outputFilePath.indexOf(".h")).toUpperCase();
        String headerHeader = "#ifndef " + headerSymbol +  "_H\n#define " + headerSymbol + "_H\n\n";
        headerHeader += "// This file was built using a java tool ConvertHTML2CStringHeader (https://github.com/jravey7/PiIoT under tools folder)."
        String headerFooter = "\n\n#endif //" + headerSymbol + "_H";

        String headerContent = "const char *" + cStringVarName + "=\n\"\\\n";
        // headerContent += "\"" + new String(Files.readAllBytes(Paths.get(htmlFilePath))) +"\";";

        BufferedReader reader = new BufferedReader( new FileReader(inputFilePath) );
        String line;
        while((line = reader.readLine()) != null)
        {
            for(int i = 0; i < line.length(); i++)
            {
                // escape double quotes and backslash
                char c = line.charAt(i);
                if((c == '"') || (c == '\\'))
                {
                    headerContent += '\\';
                }
                headerContent += c;
            }
            headerContent += "\\\n";
        }
        headerContent += "\";";

        // write c-style-string to c header file
        BufferedWriter writer;
        writer = new BufferedWriter( new FileWriter(outputFilePath) );
        writer.write(headerHeader);
        writer.write(headerContent);        
        writer.write(headerFooter);
        writer.close();

    }   
}