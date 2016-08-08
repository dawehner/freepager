<?php

namespace Drupal\Tests\freepager\Kernel;

use Drupal\KernelTests\KernelTestBase;
use Drupal\node\Entity\Node;
use Drupal\node\Entity\NodeType;
use Drupal\views\Plugin\views\display\DisplayPluginBase;
use Drupal\views\Views;
use Symfony\Component\HttpFoundation\ParameterBag;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Routing\Route;

/**
 * Tests the freepager functionality.
 *
 * @group freepager
 */
class FreepagerTest extends KernelTestBase {

  /**
   * {@inheritdoc}
   */
  public static $modules = ['views', 'node', 'user', 'system', 'freepager', 'freepager_test'];

  /**
   * @var \Drupal\node\NodeInterface[]
   */
  protected $nodes;

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();

    $this->installEntitySchema('node');
    $this->installEntitySchema('user');
    $this->installConfig('freepager_test');

    NodeType::create([
      'type' => 'page',
    ])->save();

    $this->nodes = [];
    $time = time();
    for ($i = 1; $i <= 50; $i++) {
      $node = Node::create([
        'type' => 'page',
        'title' => 'Page ' . $i,
        'created' => $time + $i,
      ]);
      $node->save();
      $this->nodes[$node->id()] = $node;
    }
  }

  /**
   * {@inheritdoc}
   */
  public function testPager() {
    // Choose node 10, node 9 and 11 should be rendered as the pager.
    $request = Request::create('/node/10');
    $request->attributes->set('_route', 'entity.node.canonical');
    $request->attributes->set('_route_object', new Route('/node/{node}'));
    $request->attributes->set('_raw_variables', new ParameterBag(['node' => 10]));
    $request->attributes->set('node', $this->nodes[10]);
    \Drupal::requestStack()->push($request);

    $view = Views::getView('pager');
    $build = DisplayPluginBase::buildBasicRenderable('pager', 'freepager_1');
    $output = $this->render($build);
    $this->setRawContent($output);

    // previous pager link.
    $this->assertLink('pager-value ' . $this->nodes[9]->getTitle());
    $this->assertLinkByHref('/node/9');
    // next pager link.
    $this->assertLink('pager-value ' . $this->nodes[11]->getTitle());
    $this->assertLinkByHref('/node/11');
    // current pager link.
    $this->assertRaw('pager-value ' . $this->nodes[10]->getTitle());
  }

}
