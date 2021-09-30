OGpic = 'new.png'; %Initializes picture
[I,map] = imread(OGpic); %takes in the picture as a 3D array of RGB Values 
gI = rgb2gray(I); %converts the picture into a greyscaled picture (Converst the 3D array to a 2D array of coordinates

[row,col] = size(gI);
csvArray = zeros(row,col);
%%compArr = zeros(90,160); %creates the desired array that we want the picture size to be
%so it is not a detailed picture and makes the pancake printer 

for i = 1:row %height of the picture
    for j = 1:col %width of the picture
        if gI(i,j) < 245
                csvArray(i,j) = 0;
        else
            csvArray(i,j) = 1;
        end
            
    end
end

csvwrite('mazePicCSV.csv',csvArray); %writes the new array as a csv for the arduino

%displays final picture
figure
imshow(gI)

