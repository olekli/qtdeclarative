import QtQuick 2.0
import QtTest 1.0
import "testhelper.js" as Helper
Canvas {
   id:canvas; width:100;height:50; renderTarget:Canvas.Image
   TestCase {
       name: "composite"; when: windowShown
       function test_clearRect() {
           var ctx = canvas.getContext('2d');
           ctx.reset();
           ctx.fillStyle = '#f00';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'destination-atop';
           ctx.clearRect(0, 0, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,0,0,0));
      }

       function test_clip_data() {
           return [ {compsite:"copy"},
                    {compsite:"destination-atop"},
                    {compsite:"destination-in"},
                    {compsite:"destination-out"},
                    {compsite:"destination-over"},
                    {compsite:"lighter"},
                    {compsite:"source-atop"},
                    {compsite:"source-in"},
                    {compsite:"source-out"},
                    {compsite:"source-over"},
                    {compsite:"xor"}
                   ];
       }

       function test_clip(data) {
           var ctx = canvas.getContext('2d');
           ctx.reset();
           ctx.fillStyle = '#0f0';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = data.compsite;
           ctx.rect(-20, -20, 10, 10);
           ctx.clip();
           ctx.fillStyle = '#f00';
           ctx.fillRect(0, 0, 50, 50);
           verify(Helper.comparePixel(ctx, 25,25, 0,255,0,255));
           verify(Helper.comparePixel(ctx, 75,25, 0,255,0,255));
       }

       function test_globalAlpha() {
           var ctx = canvas.getContext('2d');
           ctx.reset();
           compare(ctx.globalAlpha, 1.0);

           ctx.fillStyle = '#0f0';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalAlpha = 0.01; // avoid any potential alpha=0 optimisations
           ctx.fillStyle = '#f00';
           ctx.fillRect(0, 0, 100, 50);
           //verify(Helper.comparePixel(ctx, 50,25, 2,253,0,255, 2));

           ctx.reset();
           ctx.globalAlpha = 0.5;
           var a = ctx.globalAlpha; // might not be exactly 0.5, if it is rounded/quantised, so remember for future comparisons
           ctx.globalAlpha = Infinity;
           compare(ctx.globalAlpha, a);
           ctx.globalAlpha = -Infinity;
           compare(ctx.globalAlpha, a);
           ctx.globalAlpha = NaN;
           compare(ctx.globalAlpha, a);

           ctx.globalAlpha = 0.5;
           a = ctx.globalAlpha; // might not be exactly 0.5, if it is rounded/quantised, so remember for future comparisons
           ctx.globalAlpha = 1.1;
           compare(ctx.globalAlpha, a);
           ctx.globalAlpha = -0.1;
           compare(ctx.globalAlpha, a);
           ctx.globalAlpha = 0;
           compare(ctx.globalAlpha, 0);
           ctx.globalAlpha = 1;
           compare(ctx.globalAlpha, 1);

       }

       function test_operation() {
           var ctx = canvas.getContext('2d');
           ctx.reset();
           ctx.globalCompositeOperation = 'xor';
           ctx.globalCompositeOperation = 'Source-over';
           compare(ctx.globalCompositeOperation, 'xor');

           ctx.reset();
           ctx.globalCompositeOperation = 'xor';
           ctx.globalCompositeOperation = 'clear';
           compare(ctx.globalCompositeOperation, 'xor');

           ctx.reset();
           ctx.globalCompositeOperation = 'xor';
           ctx.globalCompositeOperation = 'darker';
           compare(ctx.globalCompositeOperation, 'xor');

           ctx.reset();
           compare(ctx.globalCompositeOperation, 'source-over');


           ctx.reset();
           var modes = ['source-atop', 'source-in', 'source-out', 'source-over',
               'destination-atop', 'destination-in', 'destination-out', 'destination-over',
               'lighter', 'copy', 'xor'];
           for (var i = 0; i < modes.length; ++i)
           {
               ctx.globalCompositeOperation = modes[i];
               compare(ctx.globalCompositeOperation, modes[i]);
           }

           ctx.reset();
           ctx.globalCompositeOperation = 'xor';
           ctx.globalCompositeOperation = 'highlight';
           compare(ctx.globalCompositeOperation, 'xor');

           ctx.reset();
           ctx.globalCompositeOperation = 'xor';
           ctx.globalCompositeOperation = 'source-over\\0';
           compare(ctx.globalCompositeOperation, 'xor');

           ctx.reset();
           ctx.globalCompositeOperation = 'xor';
           ctx.globalCompositeOperation = 'over';
           compare(ctx.globalCompositeOperation, 'xor');


           ctx.reset();
           ctx.globalCompositeOperation = 'xor';
           ctx.globalCompositeOperation = 'nonexistent';
           compare(ctx.globalCompositeOperation, 'xor');
       }

       function test_solid() {
           skip("FIXME");
           var ctx = canvas.getContext('2d');
           ctx.reset();
           ctx.fillStyle = Qt.rgba(0, 1, 1, 1.0);
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'copy';
           ctx.fillStyle = Qt.rgba(1, 1, 0, 1.0);
           ctx.fillRect(0, 0, 100, 50);
           //verify(Helper.comparePixel(ctx, 50,25, 255,255,0, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 255, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'destination-atop';
           ctx.fillStyle = 'rgba(255, 255, 0, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           //verify(Helper.comparePixel(ctx, 50,25, 0,255,255,255, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 255, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'destination-in';
           ctx.fillStyle = 'rgba(255, 255, 0, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           //verify(Helper.comparePixel(ctx, 50,25, 0,255,255,255, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 255, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'destination-out';
           ctx.fillStyle = 'rgba(255, 255, 0, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,0,0,0, 5));


           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 255, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'destination-over';
           ctx.fillStyle = 'rgba(255, 255, 0, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           //verify(Helper.comparePixel(ctx, 50,25, 0,255,255,255, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 255, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'lighter';
           ctx.fillStyle = 'rgba(255, 255, 0, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           //verify(Helper.comparePixel(ctx, 50,25, 255,255,255,255, 5));


           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 255, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'source-atop';
           ctx.fillStyle = 'rgba(255, 255, 0, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           //verify(Helper.comparePixel(ctx, 50,25, 255,255,0, 5));


           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 255, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'source-in';
           ctx.fillStyle = 'rgba(255, 255, 0, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           //verify(Helper.comparePixel(ctx, 50,25, 255,255,0, 5));


           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 255, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'source-out';
           ctx.fillStyle = 'rgba(255, 255, 0, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
          // verify(Helper.comparePixel(ctx, 50,25, 0,0,0,0, 5));


           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 255, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'source-over';
           ctx.fillStyle = 'rgba(255, 255, 0, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           //verify(Helper.comparePixel(ctx, 50,25, 255,255,0, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 255, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'xor';
           ctx.fillStyle = 'rgba(255, 255, 0, 1.0)';
           ctx.fillRect(0, 0, 100, 50);
           //verify(Helper.comparePixel(ctx, 50,25, 0,0,0,0, 5));
       }
       function test_transparent() {

           skip("FIXME");
           var ctx = canvas.getContext('2d');
           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'copy';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.fillRect(0, 0, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,0,255,191, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'copy';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.fillRect(0, 0, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,0,255,191, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'destination-in';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.fillRect(0, 0, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,255,0,95, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'destination-out';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.fillRect(0, 0, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,255,0,31, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'destination-over';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.fillRect(0, 0, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,145,109,223, 5));


           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'lighter';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.fillRect(0, 0, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,127,191,255, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'source-atop';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.fillRect(0, 0, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,63,191,127, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'source-in';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.fillRect(0, 0, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,0,255,95, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'source-out';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.fillRect(0, 0, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,0,255,95, 5));


           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'source-over';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.fillRect(0, 0, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,36,218,223, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'xor';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.fillRect(0, 0, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,63,191,127, 5));

       }

       function test_uncovered() {
           skip("FIXME");
           var ctx = canvas.getContext('2d');
           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'copy';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.translate(0, 25);
           ctx.fillRect(0, 50, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,0,0,0, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'destination-atop';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.translate(0, 25);
           ctx.fillRect(0, 50, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,0,0,0, 5));



           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'destination-in';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.translate(0, 25);
           ctx.fillRect(0, 50, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,0,0,0, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'source-in';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.translate(0, 25);
           ctx.fillRect(0, 50, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,0,0,0, 5));

           ctx.reset();
           ctx.fillStyle = 'rgba(0, 255, 0, 0.5)';
           ctx.fillRect(0, 0, 100, 50);
           ctx.globalCompositeOperation = 'source-out';
           ctx.fillStyle = 'rgba(0, 0, 255, 0.75)';
           ctx.translate(0, 25);
           ctx.fillRect(0, 50, 100, 50);
           verify(Helper.comparePixel(ctx, 50,25, 0,0,0,0, 5));

       }

   }
}